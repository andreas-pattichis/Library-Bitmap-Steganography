#include "bmp.h"

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

//   unsigned char c = 'a';
//    int ii = 0;
//    while (c != '\0'){
//        c = text[ii];
//
//        printf("%d [%c] -> %d\n",ii,c,c);
//        ii++;
//    }






    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    memcpy(new_pixel_array,img->pixel_array,img->pixel_array_size);
    int b,o,n = (1+strlen(text))*8,*permutations = createPermutationFunction(n,system_key);
//    printf("arr is: %d and len is %d\n",n,strlen(text));
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
    int c1;
    char c,*text;
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
//    printf("%s\n",text);
    // We know that im getting the text correctly
    return text;
}

char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key){
    char *text = calloc(textLen,sizeof(char));
    int counter = 7,text_counter = 0, character_sum = 0;
    int o = 0,n = (textLen)*8,*permutations = createPermutationFunction(n,system_key);
//    printf("arr is: %d and len is %d\n",n,textLen);

//    printf("\n\n\n------------------------------------\n\n\n");
    for (int i = 0; i < (textLen)*8; i++) {
        o = permutations[i];
//        printf("%d\n",o);
        int aa = img->pixel_array[o] & 1;
//        printf("%d",aa);
        aa = aa * pow(2,counter);
        character_sum+=aa;

        if (counter == 0) {
//            printf("\n");
            text[text_counter] = character_sum;

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

int infoEquals(const char *a, const char *b, int length){
    for (int i = 0; i < length; ++i) {
        if (a[i] != b[i]){
            return 0;
        }
    }
    return 1;
}

int imageEquals(IMAGE *a,IMAGE *b){
    int result = 0;
    if (!infoEquals(a->file_head->file_size,b->file_head->file_size,4)){
        return 0;
    }
    if (!infoEquals(a->file_head->pix_array_offset,b->file_head->pix_array_offset,4)){
        return 0;
    }
    if (!infoEquals(a->file_head->reserve_2,b->file_head->reserve_2,2)){
        return 0;
    }
    if (!infoEquals(a->file_head->reserve_1,b->file_head->reserve_1,2)){
        return 0;
    }
    if (!infoEquals(a->file_head->ident,b->file_head->ident,2)){
        return 0;
    }
    if (!infoEquals(a->info_head->img_size,b->info_head->img_size,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->height,b->info_head->height,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->width,b->info_head->width,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->important_colours,b->info_head->important_colours,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->num_colours,b->info_head->num_colours,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->vertical_res,b->info_head->vertical_res,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->horizontal_res,b->info_head->horizontal_res,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->size,b->info_head->size,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->compression_method,b->info_head->compression_method,4)){
        return 0;
    }
    if (!infoEquals(a->info_head->bbp,b->info_head->bbp,2)){
        return 0;
    }
    if (!infoEquals(a->info_head->colour_plain,b->info_head->colour_plain,2)){
        return 0;
    }
    for (int i = 0; i < a->pixel_array_size; ++i) {
        if (a->pixel_array[i] != b->pixel_array[i]){
            return 0;
        }
    }
    return 1;
}




int convert_to_anInteger(char *arr, int arrLen){
    int sum = 0,power = arrLen*8 - 1,to_and,which = 0,pos = 7,t,add;
    // reverse the arr because of little endian
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
//        printf("adding : %d (%d * %d^%d)  Which is : %d  Pos is: %d\n",add,to_and,2,power,which,pos);
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


void stringToImage(IMAGE *img, char *textFileName){
    char text[(img->height * img->width)/*/8*/];    // why

    FILE *filePointer;

    filePointer = fopen(textFileName, "r");
    if (filePointer == NULL){
        printf("File is not available \n");
        return;
    }

    int cnt = 0;
    while ((fgetc(filePointer)) != EOF) {
        if (cnt < (img->height * img->width)/8) {
            cnt++;
        }
    }
    // cnt is how many characters we can put into the image
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

    /* CHECKING IF THE FILE HAS BEEN READ CORRECTLY
    printf("\n\n%d\n\n",cnt);
    for(i=0;i<=cnt;i++)
        printf("%c",text[i]);
    printf("\n");
    */

    int bits[cnt*8+1];

    for(i=0;i<=cnt*8;i++){
        bits[i] = 128 * getBit(text, img->height * (i / img->height) + (i % img->width));
        /* TESTING TO SEE IF THE BITS HAVE BEEN
        //printf("%d\t",bits[i]);*/
    }
    int k=0;

    unsigned char *new_pixel_array = calloc(img->pixel_array_size,1);
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    // reset the row count.
            i = i + img->padding - 1; 	// skip padding, minus 1 because
            //k++;
            continue;   			    // for condition will add 1 to i;
            }

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
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
    IMAGE *new = (IMAGE *)malloc(sizeof(IMAGE));
    new->padding = img->padding;
    new->row_length = img->row_length;
    new->pixel_array_size = img->pixel_array_size;
    new->width = img->width;
    new->height = img->height;
    new->bbp = img->bbp;
    new->pixel_array = new_pixel_array;
    // Save file
    reverse_pixel_array(new);
    FILE *file = fopen("zitima7.bmp", "wb");
    fwrite(img->file_head, sizeof(FILE_HEADER), 1, file);
    fwrite(img->info_head, sizeof(INFO_HEADER), 1, file);
    fwrite(&new_pixel_array[0], 1, new->pixel_array_size, file);
    fclose(file);
}

void imageToString(IMAGE *img){
    int i,k=0;
    int row_pos = 0;
    char ch;
    int num1 = 0,num2 = 0,num3 = 0,num4 = 0,num5 = 0,num6 = 0,num7 = 0,num8 = 0;
    FILE *fout = fopen("zitima8.txt","a+");

    //Loop through the whole pixel array
    for (i = 0; i < img->pixel_array_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == img->row_length/3) {
            printf("\n");
            row_pos = 0; 			    // reset the row count.
            i = i + img->padding - 1; 	// skip padding, minus 1 because
            //k++;
            continue;   			    // for condition will add 1 to i;
        }

        num1 = img->pixel_array[i];
        num2 = img->pixel_array[i+3]>>1;
        num3 = img->pixel_array[i+6]>>2;
        num4 = img->pixel_array[i+9]>>3;
        num5 = img->pixel_array[i+12]>>4;
        num6 = img->pixel_array[i+15]>>5;
        num7 = img->pixel_array[i+18]>>6;
        num8 = img->pixel_array[i+21]>>7;

        ch =  num1+num2+num3+num4+num5+num6+num7+num8;
        fprintf(fout,"%c",ch);
        row_pos++;
    }
    fclose(fout);
}

int main(){
//    //01100011 01100001 01101110
//    for (int i = 0; i < 24; ++i) {
//        if(i%8==0)printf("\n");
//        printf("%d",getBit("can", i));
//    }

//    IMAGE *image =  load_bmp("tux-bonaparte.bmp");
//    char *text = readTextFromFile("poem.txt");
//    putTextInPicture(image,text,69);
//    IMAGE *with_text =  load_bmp("withEncodedText.bmp");
//    char *decoded_text = decodeTextFromImage(with_text,280,69);
//    printf("%s\n",decoded_text);

//    IMAGE *a =  load_bmp("tux-bonaparte.bmp");
//    IMAGE *b =  load_bmp("tux-bonaparte.bmp");
//   printf("Are pictures the same? %d\n",imageEquals(a,b));
     IMAGE *test =  load_bmp("tux-pirate.bmp");
    stringToImage( test,"poem.txt");
   // IMAGE *test1 =  load_bmp("4x3.bmp");
   // print_information(test1);
   // IMAGE *test2 =  load_bmp("image2.bmp");
    //print_information(test2);
//    char as[2] = {'\022', '\v'};
//    int s = convert_to_anInteger(as,2);
//    printf("d -> %d",s);
   // IMAGE *test2 =  load_bmp("image1.bmp");
   // createGrayscale(test2);
//    IMAGE *cover =  load_bmp("IMG_6865.bmp");
//    IMAGE *secret =  load_bmp("IMG_6875.bmp");
//    change_pixels(cover,secret,4);
//    IMAGE *coded = load_bmp("file_name.bmp");
//    decode_image(coded,4);
//    IMAGE *cover =  load_bmp("4x3.bmp");
//    IMAGE *secret =  load_bmp("4x3.bmp");

//    IMAGE *test =  load_bmp("tux-pirate.bmp");
//    stringToImage( test,"strFile.txt");
//    IMAGE *test2 =  load_bmp("zitima7.bmp");
//    imageToString(test2);

    return 0;
}
