#include "decodeText.h"

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

char *decodeTextFromImage(IMAGE *img,int textLen,unsigned int system_key){
    char *text = calloc(textLen,sizeof(char));
    int counter = 7,text_counter = 0, character_sum = 0;
    int o = 0,n = (textLen)*8,*permutations = createPermutationFunction(n,system_key);

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
    return text;
}