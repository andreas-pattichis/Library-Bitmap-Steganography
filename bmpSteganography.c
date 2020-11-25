/**
 * Client class


#include "Library.h"

int main(int args, char* argv[]) {

    if (args < 2) {
        printf("You should enter at least 2 files.\n");
        exit(1);
    }

    char *choice = argv[1];

    if(strcmp(choice,"-list") == 0){
        // LEITOURGIA 1: -LIST
        IMAGE *test11 =  load_bmp(argv[2]);
        print_information(test11);

        //IMAGE *test12 =  load_bmp(argv[2]);
        //print_information(test12);
    }
    else if(strcmp(choice,"–grayscale") == 0){
        // LEITOURGIA 2: -GREAYSCALE
        IMAGE *test21 =  load_bmp(argv[2]);
        createGrayscale(test21);
        //IMAGE *test22 =  load_bmp(argv[2]);
        //createGrayscale(test22);
    }
    else if(strcmp(choice,"–encodeStegano") == 0){
        // LEITOURGIA 3: -ENCODESTEGANO
        IMAGE *cover =  load_bmp(argv[2]);
        IMAGE *secret =  load_bmp(argv[3]);
        change_pixels(cover,secret,4);
    }
    else if(strcmp(choice,"–decodeStegano") == 0){
        // LEITOURGIA 4: -DECODESTEGANO
        IMAGE *coded = load_bmp(argv[2]);
        decode_image(coded,4);
    }
    else if(strcmp(choice,"–encodeText") == 0){
        // LEITOURGIA 5: -ENCODETEXT
        IMAGE *test5 =  load_bmp(argv[2]);
        char *text = readTextFromFile(argv[3]);
        putTextInPicture(test5,text,69);
    }
    else if(strcmp(choice,"–decodeText") == 0){
        // LEITOURGIA 6: -DECODETEXT
        IMAGE *with_text =  load_bmp(argv[2]);
        char *decoded_text = decodeTextFromImage(with_text,280,69);
        printf("%s\n",decoded_text);
    }
    else if(strcmp(choice,"–stringToImage") == 0){
        // LEITOURGIA 7: -STRINGTOIMAGE
        IMAGE *test7 =  load_bmp(argv[2]);
        stringToImage( test7,argv[3]);
    }
    else if(strcmp(choice,"–imageToString ") == 0){
        // LEITOURGIA 8: -IMAGETOSTRING
        IMAGE *test8 =  load_bmp(argv[2]);
        imageToString(test8);
    }
    else{
        printf("No such option is available.");
    }

    return 0;
} */