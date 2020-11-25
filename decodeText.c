/*
#include "Library.h"

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
 */