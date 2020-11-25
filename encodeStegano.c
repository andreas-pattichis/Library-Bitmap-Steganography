/*
#include "Library.h"

unsigned char calculate_mask(unsigned int proof_length){
    unsigned char mask = 0xff;
    int i=0;
    while (i < proof_length){
        mask-= (int)pow(2,i);
        i++;
    }
    return mask;
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
*/