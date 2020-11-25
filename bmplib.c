/**
 *  @file bmplib.c
 *  @brief Class that includes the implementation of all the functions that are used in the 8 operations.
 *
 *  @author Costa Christian (), Andreas Pattichis (apatti01)
 *  @bug No know bugs.
 */

#include "bmplib.h"


int calculate_length_of_String(char *text){
    int i = 0;
    while (1){
        if (text[i] == NULL){
            return i;
        }
        if (text[i] == '\0'){
            return i;
        }
        i++;
    }
}

int convert_to_anInteger(char *arr, int arrLen){
    int sum = 0,power = arrLen*8 - 1,to_and,which = 0,pos = 7,t,add;
    /* Reverses the arr because of little endian */
    if (arrLen == 2){
        t = arr[0];
        arr[0] = arr[1];
        arr[1] = t;
    }

    else {
        t = arr[0];
        arr[0] = arr[3];
        arr[3] = t;
        t = arr[1];
        arr[1] = arr[2];
        arr[2] = t;
    }

    while (1){
        to_and = arr[which] & (int) pow(2,pos);
        if (to_and != 0 )
            to_and = 1;
        add = to_and * pow(2,power);
        sum += add;
        if (pos % 8 == 0){
            pos = 8;
            which++;
        }
        pos--;
        power--;
        if (which == arrLen){
            break;
        }
    }

    return sum;
}

void print_information(IMAGE *img){
    /* Stores the information to the appropriate variables */
    int BMbfSize = convert_to_anInteger(img->file_head->file_size,4);
    int bfReserved1 = convert_to_anInteger(img->file_head->reserve_1,2);
    int bfReserved2 = convert_to_anInteger(img->file_head->reserve_2,2);
    int bfOffBits = convert_to_anInteger(img->file_head->pix_array_offset,4);
    int biSize = convert_to_anInteger(img->info_head->size,4);
    int biWidth = convert_to_anInteger(img->info_head->width,4);
    int biHeight = convert_to_anInteger(img->info_head->height,4);
    int biPlanes = convert_to_anInteger(img->info_head->colour_plain,2);
    int biBitCount = convert_to_anInteger(img->info_head->bbp,2);
    int biCompression = convert_to_anInteger(img->info_head->compression_method,4);
    int biSizeImage = convert_to_anInteger(img->info_head->img_size,4);
    int biXPelsPerMeter = convert_to_anInteger(img->info_head->horizontal_res,4);
    int biYPelsPerMeter = convert_to_anInteger(img->info_head->vertical_res,4);
    int biClrUsed = convert_to_anInteger(img->info_head->num_colours,4);
    int biClrImportant = convert_to_anInteger(img->info_head->important_colours,4);

    /* Prints the information */
    printf("BITMAP_FILE_HEADER\n");
    printf("==================\n");
    printf("bfType: BM\n");
    printf("BMbfSize: %d\n", BMbfSize);
    printf("bfReserved1: %d\n", bfReserved1);
    printf("bfReserved2: %d\n", bfReserved2);
    printf("bfOffBits: %d\n", bfOffBits);
    printf("\nBITMAP_INFO_HEADER\n");
    printf("==================\n");
    printf("biSize: %d\n",biSize);
    printf("biWidth: %d\n",biWidth);
    printf("biHeight: %d\n",biHeight);
    printf("biPlanes: %d\n",biPlanes);
    printf("biBitCount: %d\n",biBitCount);
    printf("biCompression: %d\n",biCompression);
    printf("biSizeImage: %d\n",biSizeImage);
    printf("biXPelsPerMeter: %d\n",biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n",biYPelsPerMeter);
    printf("biClrUsed: %d\n",biClrUsed);
    printf("biClrImportant: %d\n",biClrImportant);
    printf("\n***************************************************************************\n");
}

void createGrayscale(IMAGE *img, char *name) {

    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int i;
    int row_pos = 0;

    /* Goes through the whole pixel array */
    for (i = 0; i < img->pixel_array_size-3; i++) {
        /* Prints a new line after each row of pixels
           skip the loop count ahead of the padded bytes. */
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			            /* Resets the row count */
            i = i + img->padding - 1; 	        /* Skips padding, minus 1 */
            continue;   			            /* For condition will add 1 to i */
        }
        /* Luminance = 0.299*red + 0.587*green + 0.114*blue */
        int sum = (unsigned char)(0.114* img->pixel_array[i] + 0.587* img->pixel_array[i+1] + 0.299*img->pixel_array[i+2]);

        /* Fills the new pixel array */
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i] = (unsigned char)(sum );
        /* Advance the position we are in the row, so we know when we can skip the padding bytes */
        row_pos++;
    }

    /* Creates the new image */
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;

    /* Saves the new image */
    int file_name_length = calculate_length_of_String(name);
    char *newName = calloc(10+file_name_length+1,sizeof(char));
    strcpy(newName,"grayscale_");
    strcat(newName,name);
    FILE *file = fopen(newName, "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

unsigned char calculate_mask(unsigned int proof_length){
    unsigned char mask = 0xff;
    int i=0;
    while (i < proof_length){
        mask-= (int)pow(2,i);
        i++;
    }
    return mask;
}

void change_pixels(IMAGE *cover, IMAGE *secret,unsigned int proof_len, char *name) {

    unsigned char *new_pixel_array = malloc(cover->pixel_array_size);
    int new_arr_length = cover->pixel_array_size;
    memcpy(new_pixel_array,cover->pixel_array,new_arr_length);
    unsigned char rc,gc,bc,rs,gs,bs,rn,gn,bn;

    int i;
    int row_pos = 0;

    /* Goes through the whole pixel array */
    for (i = 0; i < cover->pixel_array_size-3; i++) {
        /* Prints a new line after each row of pixels
           skip the loop count ahead of the padded bytes. */
        if (row_pos == cover->row_length/3) {
            printf("\n");
            row_pos = 0; 			        /* Resets the row count */
            i = i + cover->padding - 1; 	/* Skips padding, minus 1 */
            continue;   			        /* For condition will add 1 to i */
        }

        /* Fills the new pixel array */
        bc = cover->pixel_array[i];
        bs = secret->pixel_array[i];
        bn = (bs >> (8-proof_len)) | (bc & calculate_mask(proof_len));
        new_pixel_array[i] = bn;
        i++;
        gc = cover->pixel_array[i];
        gs = secret->pixel_array[i];
        gn = (gs >> (8-proof_len)) | (gc & calculate_mask(proof_len));
        new_pixel_array[i] = gn;
        i++;
        rc = cover->pixel_array[i];
        rs = secret->pixel_array[i];
        rn = (rs >> (8-proof_len)) | (rc & calculate_mask(proof_len));
        new_pixel_array[i] = rn;

        /* Advance the position we are in the row, so we know when we can skip the padding bytes */
        row_pos++;
    }

    /* Creates the new image */
    IMAGE new;
    new.padding = cover->padding;
    new.row_length = cover->row_length;
    new.pixel_array_size = cover->pixel_array_size;
    new.width = cover->width;
    new.height = cover->height;
    new.bbp = cover->bbp;
    new.pixel_array = new_pixel_array;

    /* Saves the new image */
    int file_name_length = calculate_length_of_String(name);
    char *newName = calloc(4+file_name_length+1,sizeof(char));
    strcpy(newName,"new-");
    strcat(newName,name);
    FILE *file = fopen(newName, "wb");
    fwrite(cover->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(cover->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

void decode_image(IMAGE *img,unsigned int proof_len, char *name){
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    unsigned char r,g,b;

    int i;
    int row_pos = 0;

    /* Goes through the whole pixel array */
    for (i = 0; i < img->pixel_array_size-3; i++) {
        /* Prints a new line after each row of pixels
           skip the loop count ahead of the padded bytes. */
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			        /* Resets the row count */
            i = i + img->padding - 1;   	/* Skips padding, minus 1 */
            continue;   			        /* For condition will add 1 to i */
        }

        /* Fills the new pixel array */
        b = img->pixel_array[i];
        b = b << (8-proof_len);
        new_pixel_array[i] = b;
        i++;
        g = img->pixel_array[i];
        g = g << (8-proof_len);
        new_pixel_array[i] = g;
        i++;
        r = img->pixel_array[i];
        r = r << (8-proof_len);
        new_pixel_array[i] = r;

        /* Advance the position we are in the row, so we know when we can skip the padding bytes */
        row_pos++;
    }

    /* Creates the new image */
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;

    /* Saves the new image */
    int file_name_length = calculate_length_of_String(name);
    char *newName = calloc(4+file_name_length+1,sizeof(char));
    strcpy(newName,"new-");
    strcat(newName,name);
    FILE *file = fopen(newName, "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

char *readTextFromFile(char *filename){
    int c1;
    char *text;
    char c;
    int index = 0;

    FILE * fp;
    fp = fopen (filename, "r");
    if (fp==NULL){
        printf("No such file.");
        return NULL;
    }

    text = (char *)calloc(MAX_WORDS,sizeof(char));
    while (1){
        c1 = fgetc(fp);
        if (c1 == EOF){
            break;
        }
        if (c1 == '\r'){
            continue;
        }
        c = c1;
        text[index] = c;
        index++;
    }
    text[index] = '\0';
    fclose(fp);

    return text;
}

void putTextInPicture(IMAGE *img, char *text, unsigned int system_key, char *name){

    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    memcpy(new_pixel_array,img->pixel_array,img->pixel_array_size);

    int b,o,n = (1+strlen(text))*8,*permutations = createPermutationFunction(n,system_key);

    for (int i = 0; i < (1+strlen(text))*8; i++) {
        b = getBit(text,i);
        o = permutations[i];
        new_pixel_array[o] = new_pixel_array[o] & 254;
        new_pixel_array[o] = new_pixel_array[o] | b;
    }

    /* Creates the new image */
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;

    /* Saves the new image */
    int file_name_length = calculate_length_of_String(name);
    char *newName = calloc(4+file_name_length+1,sizeof(char));
    strcpy(newName,"new-");
    strcat(newName,name);
    FILE *file = fopen(newName, "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key, char *name){

    char *text = calloc(textLen,sizeof(char));
    int counter = 7,text_counter = 0, character_sum = 0;

    int o,n = (textLen) * 8,*permutations = createPermutationFunction(n, system_key);

    for (int i = 0; i < (textLen)*8; i++) {
        o = permutations[i];
        int aa = img->pixel_array[o] & 1;
        aa = aa * pow(2,counter);
        character_sum+=aa;
        if (counter == 0) {
            text[text_counter] = character_sum;

            text_counter++;
            character_sum = 0;
            counter = 7;
        }
        else counter--;
    }

    FILE *fout = fopen( name,"w");
    fprintf(fout,"%s",text);
    fclose(fout);
    return text;
}

void stringToImage(IMAGE *img, char *textFileName, char *name){

    char text[(img->height * img->width)/8];

    FILE *filePointer;
    filePointer = fopen(textFileName, "r");
    if (filePointer == NULL){
        printf("File is not available \n");
        return;
    }

    int cnt = 0; // cnt is how many characters we can put into the image
    while ((fgetc(filePointer)) != EOF) {
        if (cnt < (img->height * img->width)/8) {
            cnt++;
        }
    }
    fclose(filePointer);

    filePointer = fopen(textFileName, "r");
    if (filePointer == NULL){
        printf("File is not available \n");
        return;
    }

    int i=0;
    char ch;
    while (i<=cnt) {
        ch = fgetc(filePointer);
        text[i] = ch;
        i++;
    }

    // now we have put our text in the array
    fclose(filePointer);
    int bits[cnt*8];
    for(int ii=0;ii<cnt*8;ii++){
        bits[ii] = 128 * getBit(text,ii);
    }

    int k=0;
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int row_pos = 0;

    /* Goes through the whole pixel array */
    for (i = 0; i < img->pixel_array_size-3; i++) {
        /* Prints a new line after each row of pixels
           skip the loop count ahead of the padded bytes. */
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    /* Resets the row count */
            i = i + img->padding - 1; 	/* Skips padding, minus 1 */
            continue;   			    /* For condition will add 1 to i */
        }

        /* Fills the new pixel array */
        if(bits[k]==128){
            new_pixel_array[i++] = (unsigned char)(128);
            new_pixel_array[i++] = (unsigned char)(128);
            new_pixel_array[i] = (unsigned char)(128);
        }
        else{
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i] = (unsigned char)(0);
        }

        k++;

        /* Advance the position we are in the row, so we know when we can skip the padding bytes */
        row_pos++;
    }

    /* Creates the new image */
    IMAGE *new = (IMAGE *)malloc(sizeof(IMAGE));
    new->padding = img->padding;
    new->row_length = img->row_length;
    new->pixel_array_size = img->pixel_array_size;
    new->width = img->width;
    new->height = img->height;
    new->bbp = img->bbp;
    new->pixel_array = new_pixel_array;

    /* Saves the new image */
    int file_name_length = calculate_length_of_String(name);
    char *newName = calloc(4+file_name_length+1,sizeof(char));
    strcpy(newName,"new-");
    strcat(newName,name);
    FILE *file = fopen(newName, "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new->pixel_array_size, file);
    fclose(file);
}

void imageToString(IMAGE *img){
    int i,sum = 0;
    int row_pos = 0;
    char ch;
    int num;

    FILE *fout = fopen("outputText.txt","w");

    /* Goes through the whole pixel array */
    for (i = 0; i < img->pixel_array_size-24; i+=24) {

        for (int g = 0, po = 7; g <= 21; po--, g+=3) {

            num = img->pixel_array[i+g];
            if (num != 0 ){
                num = 1*pow(2,po);
            }
            sum+=num;
        }

        ch =  sum;
        fprintf(fout,"%c",ch);
        row_pos++;
        sum = 0;
    }
    fclose(fout);
}