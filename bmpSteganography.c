#include "bmp.h"
#include "bmplib.h"

int main(int args, char* argv[]) {
    if (args < 2) {
        printf("You should enter at least 2 files.\n");
        exit(1);
    }

    char *choice = argv[1];
    printf("choice is: [%s]\n",choice);
    if(strcmp(choice,"-list") == 0){
        // FUNCTION 1: -LIST
        IMAGE *test11 =  load_bmp(argv[2]);
        print_information(test11);

        //IMAGE *test12 =  load_bmp(argv[2]);
        //print_information(test12);
    }
    else if(strcmp(choice,"–grayscale") == 0){
        // FUNCTION 2: -GRAYSCALE
        IMAGE *test21 =  load_bmp(argv[2]);
        createGrayscale(test21);
        //IMAGE *test22 =  load_bmp(argv[2]);
        //createGrayscale(test22);
    }
    else if(strcmp(choice,"-encodeStegano") == 0){
        // FUNCTION 3: -ENCODE_STEGANOGRAPHY
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *cover =  load_bmp(argv[3]);
        IMAGE *secret =  load_bmp(argv[4]);
        change_pixels(cover,secret,nBits);
    }
    else if(strcmp(choice,"-decodeStegano") == 0){
        // FUNCTION 4: -DECODE_STEGANOGRAPHY
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *coded = load_bmp(argv[3]);
        decode_image(coded,nBits);
    }
    else if(strcmp(choice,"-encodeText") == 0){
        // FUNCTION 5: -ENCODE_TEXT
        IMAGE *test5 =  load_bmp(argv[2]);
        char *text = readTextFromFile(argv[3]);
        putTextInPicture(test5,text,69);
    }
    else if(strcmp(choice,"–decodeText") == 0){
        // FUNCTION 6: -DECODE_TEXT
        IMAGE *with_text =  load_bmp(argv[2]);
        char *decoded_text = decodeTextFromImage(with_text,280,69);
        printf("%s\n",decoded_text);
    }
    else if(strcmp(choice,"–stringToImage") == 0){
        // FUNCTION 7: -STRING_TO_IMAGE
        IMAGE *test7 =  load_bmp(argv[2]);
        stringToImage( test7,argv[3]);
    }
    else if(strcmp(choice,"–imageToString") == 0){
        // FUNCTION 8: -IMAGE_TO_STRING
        IMAGE *test8 =  load_bmp(argv[2]);
        imageToString(test8);
    }
    else{
        printf("No such option is available.");
    }

    return 0;
}