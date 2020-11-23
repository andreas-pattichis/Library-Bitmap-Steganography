#include "bmp.h"
#include <math.h>
#include <string.h>

#define MAX_WORDS 5000

void waterproof(IMAGE *cover, IMAGE *secret,int proof_len){
    if (cover->height != secret->height || cover->width != secret->width){
        printf("The 2 pictures you have entered do not have the same dimensions.\n");
        return;
    }
}

/*
 * Open file. In case of error, print message and exit.
 */
FILE *open_file(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s", filename);

        exit(EXIT_FAILURE);
    }

    return fp;
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

void print_new_pixel_array(const unsigned char *arr,int arr_size,int r_len,int padd) {
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < arr_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == r_len/3) {
            printf("\n");
            row_pos = 0; 			    //reset the row count.
            i = i + padd - 1; 	        //skip padding, minus 1 because
            continue;   			    //for condition will add 1 to i;
        }
        unsigned char b = arr[i++];
        unsigned char g = arr[i++];
        unsigned char r = arr[i];
        printf("R=%x \tG=%x \tB=%x\n",r,g,b);
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
}

void change_pixels(IMAGE *cover, IMAGE *secret,unsigned int proof_len) {
    unsigned char *new_pixel_array = malloc(cover->pixel_array_size);
    int new_padding = cover->padding;
    int new_arr_length = cover->pixel_array_size;
    printf ("new length is: %d\n",new_arr_length);
    int new_row_length = cover->row_length;
    memcpy(new_pixel_array,cover->pixel_array,new_arr_length);
    unsigned char rc,gc,bc,rs,gs,bs,rn,gn,bn;
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < cover->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == cover->row_length/3) {
            printf("\n");
            row_pos = 0; 			        // reset the row count.
            i = i + cover->padding - 1; 	// skip padding, minus 1 because
            continue;   			        // for condition will add 1 to i;
        }
        bc = cover->pixel_array[i];
//        printf("Cover blue is: %x \t\t\t\t\t",bc);
        bs = secret->pixel_array[i];
//        printf("Secret blue is: %x \t\t\t\t\t",bs);
        bn = (bs >> (8-proof_len)) | (bc & calculate_mask(proof_len));
//        printf("New blue is: %x\n",bn);
        new_pixel_array[i] = bn;
        i++;
        gc = cover->pixel_array[i];
//        printf("Cover green is: %x \t\t\t\t\t",gc);
        gs = secret->pixel_array[i];
//        printf("Secret green is: %x \t\t\t\t\t",gs);
        gn = (gs >> (8-proof_len)) | (gc & calculate_mask(proof_len));
//        printf("New green is: %x\n",gn);
        new_pixel_array[i] = gn;
        i++;
        rc = cover->pixel_array[i];
//        printf("Cover red is: %x \t\t\t\t\t",rc);
        rs = secret->pixel_array[i];
//        printf("Secret red is: %x \t\t\t\t\t",rs);
        rn = (rs >> (8-proof_len)) | (rc & calculate_mask(proof_len));
//        printf("New red is: %x\n",rn);
        new_pixel_array[i] = rn;

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }

    IMAGE new;
    new.padding = cover->padding;
    new.row_length = cover->row_length;
    new.pixel_array_size = cover->pixel_array_size;
    new.width = cover->width;
    new.height = cover->height;
    new.bbp = cover->bbp;
    new.pixel_array = new_pixel_array;
    // Save file
    FILE *file = fopen("file_name.bmp", "wb");
    fwrite(cover->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(cover->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);



//    print_new_pixel_array(new_pixel_array,new_arr_length,new_row_length,new_padding);
}


int getBit(char *m, int n){
    if(n>=0 && n<=8*strlen(m)) {
        int i = n / 8;
        char ch = m[i];
        int bitStatus;
        bitStatus = (ch >> 7 - (n % 8)) & 1;
        return bitStatus;
    }
    return 0;
}

int *createPermutationFunction(int n, unsigned int system_key){
    srand(system_key);
    int temp;
    int *arr = calloc(n,sizeof(int));
    // fill array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < n; i++) {
       int a = rand() % n;
       int b = rand() % n;
       temp = arr[a];
       arr[a] = arr[b];
       arr[b] = temp;
    }
    return arr;
}

void putTextInPicture(IMAGE *img, char *text, unsigned int system_key){
   unsigned char c = 'a';
    int ii = 0;
    while (c != '\0'){
        c = text[ii];

        printf("%d [%c]\n",ii,c);
        ii++;
    }






    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    memcpy(new_pixel_array,img->pixel_array,img->pixel_array_size);
    int b,o,n = (1+strlen(text))*8,*permutations = createPermutationFunction(n,system_key);
    printf("arr is: %d and len is %d\n",n,strlen(text));
    for (int i = 0; i < (1+strlen(text))*8; i++) {
        b = getBit(text,i);
        o = permutations[i];
//        printf("%d\n",o);
        new_pixel_array[o] = new_pixel_array[o] & 254;
        new_pixel_array[o] = new_pixel_array[o] | b;
    }
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;
    // Save file
    FILE *file = fopen("withEncodedText.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

char *readTextFromFile(char *filename){
    char c,*text;
    int index = 0;
    FILE * fp;
    fp = fopen (filename, "r");
    if (fp==NULL){
        printf("No such file.");
        return NULL;
    }
    text = (char *)calloc(MAX_WORDS,sizeof(char));
    while ((c = fgetc(fp)) != EOF){
        text[index] = c;
        index++;
    }
    fclose(fp);
//    printf("%s\n",text);
    // We know that im getting the text correctly
    return text;
}

char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key){
    char *text = calloc(textLen,sizeof(char));
    int counter = 7,text_counter = 0, character_sum = 0;
    int o = 0,n = (1+textLen)*8,*permutations = createPermutationFunction(n,system_key);
    printf("arr is: %d and len is %d\n",n,textLen);

    printf("\n\n\n------------------------------------\n\n\n");
    for (int i = 0; i < (1+textLen)*8; i++) {
        o = permutations[i];
//        printf("%d\n",o);
        int aa = img->pixel_array[o] & 1;
//        printf("%d",aa);
        aa = aa * pow(2,counter);
        character_sum+=aa;

        if (counter == 0) {
//            printf("\n");
            text[text_counter] = character_sum +'0';
            text_counter++;
            character_sum = 0;
            counter = 7;
        }
        else counter--;
//        b = getBit(text,i);
//        o = permutations[i];
//        img->pixel_array[o] = img->pixel_array[o] & 254;
//        img->pixel_array[o] = img->pixel_array[o] & b;
    }
    return text;
}


void decode_image(IMAGE *img,unsigned int proof_len){
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int new_arr_length = img->pixel_array_size;
    //   memcpy(new_pixel_array,img->pixel_array,new_arr_length);
    unsigned char r,g,b;
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			        // reset the row count.
            i = i + img->padding - 1;   	// skip padding, minus 1 because
            continue;   			        // for condition will add 1 to i;
        }
        b = img->pixel_array[i];
//        printf("Original is %x\n",b);
        b = b << (8-proof_len);
//        printf("After << is %x\n",b);
//        b = b & calculate_mask(proof_len);
//        printf("Final is %x\n",b);
        new_pixel_array[i] = b;
        i++;
        g = img->pixel_array[i];
        g = g << (8-proof_len);
//        g = g & calculate_mask(proof_len);
        new_pixel_array[i] = g;
        i++;
        r = img->pixel_array[i];
        r = r << (8-proof_len);
//        r = r & calculate_mask(proof_len);
        new_pixel_array[i] = r;

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }

    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;
    // Save file
    FILE *file = fopen("decoded.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}

void createGrayscale(IMAGE *img) {
    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    //reset the row count.
            i = i + img->padding - 1; 	        //skip padding, minus 1 because
            continue;   			    //for condition will add 1 to i;
        }

        // Luminance = (2 * Red + 5 * Green + 1 * Blue) / 8
        // int sum = img->pixel_array[i] << 1;                             // Blue
        // sum += img->pixel_array[i+1] << 2 + img->pixel_array[i+1];      // Green
        // sum += img->pixel_array[i+2];                                   // Red
        // [i++] =  (unsigned char)(sum >> 3);
        // new_pixel_array[i++] =  (unsigned char)(sum >> 3);
        // new_pixel_array[i+] =  (unsigned char)(sum >> 3);
        // img->pixel_array[i++] = (unsigned char)(sum >> 3);
        // img->pixel_array[i++] = (unsigned char)(sum >> 3);
        // img->pixel_array[i] = (unsigned char)(sum >> 3);


        int sum = (unsigned char)(0.114* img->pixel_array[i] + 0.587* img->pixel_array[i+1] + 0.299*img->pixel_array[i+2]);
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i++] = (unsigned char)(sum );
        new_pixel_array[i] = (unsigned char)(sum );

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
    IMAGE new;
    new.padding = img->padding;
    new.row_length = img->row_length;
    new.pixel_array_size = img->pixel_array_size;
    new.width = img->width;
    new.height = img->height;
    new.bbp = img->bbp;
    new.pixel_array = new_pixel_array;
    // Save file
    FILE *file = fopen("grayscaled.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
    fclose(file);
}



void stringToImage(IMAGE *img, char *textFile){
    int bits[img->height * img->width];
    char text[img->height * img->width];
    //1
    FILE *filePointer;
    char ch;
    //2
    filePointer = fopen(textFile, "r");
    //3
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else {
        //4
        int cnt = 0;
        while ((ch = fgetc(filePointer)) != EOF) {
            if (cnt < img->height * img->width) {
                printf("%c", ch);
                text[cnt] = ch;
                cnt++;
            }
        }

        printf("\n");
        for (int k = 0; k < img->height * img->width; k++) {
            bits[k] = 128 * getBit(text, img->height * (k / img->height) + (k % img->width));
            printf("%d\t", bits[k]);
        }

        unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
        int i;
        int row_pos = 0;
        //Loop through the whole pixel array
        for (i = 0; i < img->pixel_array_size-3; i++) {
            //print a new line after each row of pixels
            // skip the loop count ahead of the padded bytes
            if (row_pos == img->row_length/3) {
                printf("\n");
                row_pos = 0; 			    // reset the row count.
                i = i + img->padding - 1; 	// skip padding, minus 1 because
                continue;   			    // for condition will add 1 to i;
            }

        // Luminance = (2 * Red + 5 * Green + 1 * Blue) / 8
        // int sum = img->pixel_array[i] << 1;                             // Blue
        // sum += img->pixel_array[i+1] << 2 + img->pixel_array[i+1];      // Green
        // sum += img->pixel_array[i+2];                                   // Red
        // [i++] =  (unsigned char)(sum >> 3);
        // new_pixel_array[i++] =  (unsigned char)(sum >> 3);
        // new_pixel_array[i+] =  (unsigned char)(sum >> 3);
        // img->pixel_array[i++] = (unsigned char)(sum >> 3);
        // img->pixel_array[i++] = (unsigned char)(sum >> 3);
        // img->pixel_array[i] = (unsigned char)(sum >> 3);


        if(bits[i/3]==128){
            new_pixel_array[i++] = (unsigned char)(255);
            new_pixel_array[i++] = (unsigned char)(255);
            new_pixel_array[i] = (unsigned char)(255);
        }
        else{
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i++] = (unsigned char)(0);
            new_pixel_array[i] = (unsigned char)(0);
        }

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
        IMAGE new;
        new.padding = img->padding;
        new.row_length = img->row_length;
        new.pixel_array_size = img->pixel_array_size;
        new.width = img->width;
        new.height = img->height;
        new.bbp = img->bbp;
        new.pixel_array = new_pixel_array;
        // Save file
        FILE *file = fopen("zitima7.bmp", "wb");
        fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
        fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
        fwrite(&new_pixel_array[0], 1, new.pixel_array_size, file);
        fclose(file);
    }
    //5
    fclose(filePointer);

}

int main(){
//    //01100011 01100001 01101110
//    for (int i = 0; i < 24; ++i) {
//        if(i%8==0)printf("\n");
//        printf("%d",getBit("can", i));
//    }
   // IMAGE *image =  load_bmp("tux-bonaparte.bmp");
   // char *text = readTextFromFile("poem.txt");
   // putTextInPicture(image,text,69);
   // IMAGE *with_text =  load_bmp("withEncodedText.bmp");
   // char *decoded_text = decodeTextFromImage(with_text,285,69);
   // printf("%s\n",decoded_text);
    IMAGE *test =  load_bmp("tux-pirate.bmp");
     stringToImage( test,"poem.txt");
    //IMAGE *test1 =  load_bmp("4x3.bmp");
   // print_information(test1);
    //IMAGE *test2 =  load_bmp("image2.bmp");
    //print_information(test2);

   // IMAGE *test2 =  load_bmp("image1.bmp");
   // createGrayscale(test2);
//    IMAGE *cover =  load_bmp("IMG_6865.bmp");
//    IMAGE *secret =  load_bmp("IMG_6875.bmp");
//    change_pixels(cover,secret,4);
//    IMAGE *coded = load_bmp("file_name.bmp");
//    decode_image(coded,4);
//    IMAGE *cover =  load_bmp("4x3.bmp");
//    IMAGE *secret =  load_bmp("4x3.bmp");
    return 0;
}