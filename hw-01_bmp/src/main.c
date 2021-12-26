#include <string.h>
#include <stdio.h>

#include "bmp.h"


int main(int argc, char *argv[]){
    if(argc != 8){
        return -1;
    }
    char *task = argv[1];
    char *inputFile = argv[2];
    char *outputFile = argv[3];
    int xStart = atoi(argv[4]);
    int yStart = atoi(argv[5]);
    int width = atoi(argv[6]);
    int height = atoi(argv[7]);
    if (strcmp(task, "crop-rotate")){
        return -1;
    }
    Bitmap *bmp = loadBitmap(inputFile);
    if(!bmp){
        return -1;
    }
    int result;
    result = crop(bmp, xStart, yStart, width, height);
    if(result){
        printf("Dead1");
        bmpDestructor(bmp);
        return -1;
    }
    result = rotate(bmp);
    if(result){
        printf("Dead2");
        bmpDestructor(bmp);
        return -1;
    }
    FILE * output = fopen(outputFile, "wb");
    if(!output){
        return -1;
    }
    result = saveBitmap(output, bmp);
    fclose(output);
    bmpDestructor(bmp);
    return result;

}