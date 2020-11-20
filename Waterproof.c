#include "bmp.h"
#include <math.h>
#include <string.h>

void waterproof(IMAGE *cover, IMAGE *secret,int proof_len){
    if (cover->height != secret->height || cover->width != secret->width){
        printf("The 2 pictures you have entered do not have the same dimensions.\n");
        return;
    }

}

unsigned char calculate_mask(u_int proof_length){
    unsigned char mask = 0xff;
    int i=0;
    while (i < proof_length){
        mask-= (int)pow(2,i);
        i++;
    }
    return mask;
}

void print_new_pixel_array(const u_char *arr,int arr_size,int r_len,int padd) {
    int i;
    int row_pos = 0;
    //Loop through the whole pixel array
    for (i = 0; i < arr_size-3; i++) {
        //print a new line after each row of pixels
        // skip the loop count ahead of the padded bytes
        if (row_pos == r_len/3) {
            printf("\n");
            row_pos = 0; 			    //reset the row count.
            i = i + padd - 1; 	//skip padding, minus 1 because
            continue;   			    //for condition will add 1 to i;
        }
        u_char b = arr[i++];
        u_char g = arr[i++];
        u_char r = arr[i];
        printf("R=%x \tG=%x \tB=%x\n",r,g,b);
        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
}

void change_pixels(IMAGE *cover, IMAGE *secret,u_int proof_len) {
    u_char *new_pixel_array = malloc(cover->pixel_array_size);
    int new_padding = cover->padding;
    int new_arr_length = cover->pixel_array_size;
    printf ("new length is: %d\n",new_arr_length);
    int new_row_length = cover->row_length;
    memcpy(new_pixel_array,cover->pixel_array,new_arr_length);
    u_char rc,gc,bc,rs,gs,bs,rn,gn,bn;
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
        printf("Cover blue is: %x \t\t\t\t\t",bc);
        bs = secret->pixel_array[i];
        printf("Secret blue is: %x \t\t\t\t\t",bs);
        bn = (bs >> (8-proof_len)) | (bc & calculate_mask(proof_len));
        printf("New blue is: %x\n",bn);
        new_pixel_array[i] = bn;
        i++;
        gc = cover->pixel_array[i];
        printf("Cover green is: %x \t\t\t\t\t",gc);
        gs = secret->pixel_array[i];
        printf("Secret green is: %x \t\t\t\t\t",gs);
        gn = (gs >> (8-proof_len)) | (gc & calculate_mask(proof_len));
        printf("New green is: %x\n",gn);
        new_pixel_array[i] = gn;
        i++;
        rc = cover->pixel_array[i];
        printf("Cover red is: %x \t\t\t\t\t",rc);
        rs = secret->pixel_array[i];
        printf("Secret red is: %x \t\t\t\t\t",rs);
        rn = (rs >> (8-proof_len)) | (rc & calculate_mask(proof_len));
        printf("New red is: %x\n",rn);
        new_pixel_array[i] = gn;

        //advance the position we are in the row, so we know when we can skip the padding bytes
        row_pos++;
    }
    print_new_pixel_array(new_pixel_array,new_arr_length,new_row_length,new_padding);
}

int main(){
//    IMAGE *cover =  load_bmp("IMG_6865.bmp");
//    IMAGE *secret =  load_bmp("IMG_6875.bmp");
    IMAGE *cover =  load_bmp("4x3.bmp");
    IMAGE *secret =  load_bmp("4x3.bmp");

    change_pixels(cover,secret,2);
    return 0;
}
