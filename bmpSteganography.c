/**
 *  @file bmpSteganography.c
 *  @brief Class that is used as a client.
 *
 *  @author Costa Christian (), Andreas Pattichis (apatti01)
 *  @bug No know bugs.
 */

/* Libraries included */
#include "bmp.h"
#include "bmplib.h"

int main(int args, char* argv[]) {
    if (args < 2) {
        printf("You should enter at least 2 files.\n");
        exit(1);
    }

    char *choice = argv[1];
    printf("choice is: [%s]\n",choice);

    // FUNCTION 1: -LIST
    if(strcmp(choice,"-list") == 0){
        int i;
        for(i=2;i<args;i++) {
            IMAGE *test1 = load_bmp(argv[i]);
            print_information(test1);
        }
    }

    // FUNCTION 2: -GRAYSCALE
    else if(strcmp(choice,"-grayscale") == 0){
        int i;
        for(i=2;i<args;i++) {
            IMAGE *test2 = load_bmp(argv[i]);
            createGrayscale(test2,argv[i]);
        }
    }

    // FUNCTION 3: -ENCODE_STEGANOGRAPHY
    else if(strcmp(choice,"-encodeStegano") == 0){
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *cover =  load_bmp(argv[3]);
        IMAGE *secret =  load_bmp(argv[4]);
        change_pixels(cover,secret,nBits,argv[3]);
    }

    // FUNCTION 4: -DECODE_STEGANOGRAPHY
    else if(strcmp(choice,"-decodeStegano") == 0){
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *coded = load_bmp(argv[3]);
        decode_image(coded,nBits,argv[3]);
    }

    // FUNCTION 5: -ENCODE_TEXT
    else if(strcmp(choice,"-encodeText") == 0){
        IMAGE *test5 =  load_bmp(argv[2]);
        char *text = readTextFromFile(argv[3]);
        putTextInPicture(test5,text,69,argv[2]);
    }

    // FUNCTION 6: -DECODE_TEXT
    else if(strcmp(choice,"-decodeText") == 0){
        IMAGE *with_text =  load_bmp(argv[2]);
        char *decoded_text = decodeTextFromImage(with_text,280,69,argv[4]);
        printf("%s\n",decoded_text);
    }

    // FUNCTION 7: -STRING_TO_IMAGE
    else if(strcmp(choice,"-stringToImage") == 0){
        IMAGE *test7 =  load_bmp(argv[2]);
        stringToImage( test7,argv[3],argv[2]);
    }

    // FUNCTION 8: -IMAGE_TO_STRING
    else if(strcmp(choice,"-imageToString") == 0){
        // FUNCTION 8: -IMAGE_TO_STRING
        IMAGE *test8 =  load_bmp(argv[2]);
        imageToString(test8);
    }
    else{
        printf("No such option is available.");
    }

    return 0;
}