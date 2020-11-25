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

    // FUNCTION 1: -LIST
    if(strcmp(choice,"-list") == 0){
        int i;
        for(i=2;i<args;i++) {
            IMAGE *test1 = load_bmp(argv[i]);

            if((test1->file_head->ident[0]!='B' || test1->file_head->ident[1]!='M')|| (convert_to_anInteger(test1->info_head->bbp,2) != 24)|| (convert_to_anInteger(test1->info_head->compression_method,4)!=0)){
                printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -list 4x3.bmp image2.bmp");
                return EXIT_FAILURE;
            }

            print_information(test1);
        }
    }

    // FUNCTION 2: -GRAYSCALE
    else if(strcmp(choice,"-grayscale") == 0){
        int i;
        for(i=2;i<args;i++) {
            IMAGE *test2 = load_bmp(argv[i]);

            if((test2->file_head->ident[0]!='B' || test2->file_head->ident[1]!='M')|| (convert_to_anInteger(test2->info_head->bbp,2) != 24)|| (convert_to_anInteger(test2->info_head->compression_method,4)!=0)){
                printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -grayscale image1.bmp [ image2.bmp image3.bmp ...]");
                return EXIT_FAILURE;
            }

            createGrayscale(test2,argv[i]);
        }
    }

    // FUNCTION 3: -ENCODE_STEGANOGRAPHY
    else if(strcmp(choice,"-encodeStegano") == 0){
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *cover =  load_bmp(argv[3]);
        IMAGE *secret =  load_bmp(argv[4]);

        if((cover->file_head->ident[0]!='B' || cover->file_head->ident[1]!='M')|| (convert_to_anInteger(cover->info_head->bbp,2) != 24)|| (convert_to_anInteger(cover->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -encodeStegano nbBits coverImage.bmp secretImage.bmp");
            return EXIT_FAILURE;
        }

        if((secret->file_head->ident[0]!='B' || secret->file_head->ident[1]!='M')|| (convert_to_anInteger(secret->info_head->bbp,2) != 24)|| (convert_to_anInteger(secret->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -encodeStegano nbBits coverImage.bmp secretImage.bmp");
            return EXIT_FAILURE;
        }

        change_pixels(cover,secret,nBits,argv[3]);
    }

    // FUNCTION 4: -DECODE_STEGANOGRAPHY
    else if(strcmp(choice,"-decodeStegano") == 0){
        char *num = argv[2];
        int nBits = (int) (num[0] - '0');
        IMAGE *coded = load_bmp(argv[3]);

        if((coded->file_head->ident[0]!='B' || coded->file_head->ident[1]!='M')|| (convert_to_anInteger(coded->info_head->bbp,2) != 24)|| (convert_to_anInteger(coded->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -decodeStegano nbBits encryptedImage.bmp");
            return EXIT_FAILURE;
        }

        decode_image(coded,nBits,argv[3]);
    }

    // FUNCTION 5: -ENCODE_TEXT
    else if(strcmp(choice,"-encodeText") == 0){
        IMAGE *test5 =  load_bmp(argv[2]);

        if((test5->file_head->ident[0]!='B' || test5->file_head->ident[1]!='M')|| (convert_to_anInteger(test5->info_head->bbp,2) != 24)|| (convert_to_anInteger(test5->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -encodeText coverImage.bmp inputText.txt");
            return EXIT_FAILURE;
        }

        test5 =  load_bmp(argv[2]);
        char *text = readTextFromFile(argv[3]);
        putTextInPicture(test5,text,69,argv[2]);
    }

    // FUNCTION 6: -DECODE_TEXT
    else if(strcmp(choice,"-decodeText") == 0){
        IMAGE *with_text =  load_bmp(argv[2]);
        decodeTextFromImage(with_text,280,69,argv[4]);

        if((with_text->file_head->ident[0]!='B' || with_text->file_head->ident[1]!='M')|| (convert_to_anInteger(with_text->info_head->bbp,2) != 24)|| (convert_to_anInteger(with_text->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -decodeText encryptedImage.bmp msgLength output.txt");
            return EXIT_FAILURE;
        }

        with_text =  load_bmp(argv[2]);
        char *decoded_text = decodeTextFromImage(with_text,280,69,argv[4]);
        printf("%s\n",decoded_text);
    }

    // FUNCTION 7: -STRING_TO_IMAGE
    else if(strcmp(choice,"-stringToImage") == 0){
        IMAGE *test7 =  load_bmp(argv[2]);

        if((test7->file_head->ident[0]!='B' || test7->file_head->ident[1]!='M')|| (convert_to_anInteger(test7->info_head->bbp,2) != 24)|| (convert_to_anInteger(test7->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -stringToImage sampleImage.bmp inputText.txt");
            return EXIT_FAILURE;
        }

        test7 =  load_bmp(argv[2]);
        stringToImage( test7,argv[3],argv[2]);
    }

    // FUNCTION 8: -IMAGE_TO_STRING
    else if(strcmp(choice,"-imageToString") == 0){
        // FUNCTION 8: -IMAGE_TO_STRING
        IMAGE *test8 =  load_bmp(argv[2]);


        if((test8->file_head->ident[0]!='B' || test8->file_head->ident[1]!='M')|| (convert_to_anInteger(test8->info_head->bbp,2) != 24)|| (convert_to_anInteger(test8->info_head->compression_method,4)!=0)){
            printf("Wrong input!\n\nConsider this format:\n$./bmpSteganography -imageToString encryptedTextImage.bmp");
            return EXIT_FAILURE;
        }

        test8 =  load_bmp(argv[2]);
        imageToString(test8);
    }
    else{
        printf("No such option is available.");
    }

    return 0;
}