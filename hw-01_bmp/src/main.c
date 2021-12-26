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
    int result;
    result = crop(bmp, xStart, yStart, width, height);
    if(result){
        bmpDestructor(bmp);
        return -1;
    }
    result = rotate(bmp);
    if(result){
        bmpDestructor(bmp);
        return -1;
    }
    result = saveBitmap(outputFile, bmp);
    bmpDestructor(bmp);
    return result;

}