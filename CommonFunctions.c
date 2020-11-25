#include "CommonFunctions.h"

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
