#include <stdarg.h>

#include "bmp.h"


static char * arrayConstructor(size_t elementSize, int height, int width){
    char **resultArray = malloc(sizeof(char *) * height);
    char *data = malloc(elementSize * width * height);
    if(!data || !resultArray){
        free(data);
        free(resultArray);
        return NULL;
    }
    int length = elementSize * width;
    for (int i = 0; i < height; i++){
        resultArray[i] = data + i * length;
    }
    return (char *)resultArray;
}

static void arrayDestructor(pixel **array){
    free(array[0]);
    free(array);
}

static void * massiveFree (const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    while(*fmt != '\0'){
        switch (*fmt)
        {
        case 'f':
            fclose(va_arg(args, FILE *));
            break;
        case 'p':
            arrayDestructor(va_arg(args, pixel **));
            break;
        case 'h':
            free(va_arg(args, bmpHeader *));
            break;
        case 'b':
            free(va_arg(args, Bitmap *));
            break;
        default:
            break;
        }
        fmt++;
    }
    return NULL;
}

static int countShift(int width){
    return (4 - (width * PIXEL_SIZE) % 4) % 4;
}

static Bitmap *bmpConstructor(bmpHeader *header, pixel **data){
    Bitmap *img = malloc(sizeof(Bitmap));
    if (!img){
        return NULL;
    }
    img->header = header;
    img->data = data;
    return img;
}

static void bmpReplacer(Bitmap *img, bmpHeader *header, pixel **data){
    massiveFree("hp", img->header, img->data);
    img->header = header;
    img->data = data;
}

void bmpDestructor(Bitmap *img){
    if (!img){
        return;
    }
    massiveFree("hpb", img->header, img->data, img);
}

static bmpHeader * headerConstructor(bmpHeader *oldHeader, int width, int height){
    bmpHeader *newHeader = malloc(sizeof(bmpHeader));
    if(!newHeader){
        return NULL;
    }
    int sizeImage = (width * PIXEL_SIZE + countShift(width)) * height;
    int sizeFile = oldHeader->sizeFile - oldHeader->sizeImage + sizeImage;
    *newHeader = *oldHeader;
    newHeader->sizeImage = sizeImage;
    newHeader->sizeFile = sizeFile;
    newHeader->width = width;
    newHeader->height = height;
    return newHeader;
}

Bitmap *loadBitmap(const char *inputFile){
    FILE *file = fopen(inputFile, "rb");
    if (!file){
        return NULL;
    }
    bmpHeader *header = malloc(sizeof(bmpHeader));
    if (!fread(header, 1, sizeof(bmpHeader), file)){
        return (Bitmap *) massiveFree("fh", file, header);
    }
    int width = header->width;
    int height = header->height;
    pixel **data = (pixel **)arrayConstructor(sizeof(pixel), height, width);
    if (!data){
        return (Bitmap *) massiveFree("fh", file, header);
    }
    int shift = countShift(width);
    fseek(file, header->offBits, SEEK_SET);
    for (int i = height - 1; i >= 0; i--){
        if ((int) fread(data[i], sizeof(pixel), width, file) != width){
            return (Bitmap *) massiveFree("fh", file, header);
        }
        fseek(file, shift, SEEK_CUR);
    }
    fclose(file);
    Bitmap *img = bmpConstructor(header, data);
    if (!img){
        return (Bitmap *) massiveFree("hp", header, data);
    }
    return img;
}

int saveBitmap(FILE *file, Bitmap *img){
    if (!fwrite(img->header, sizeof(bmpHeader), 1, file)){
        fclose(file);
        return 1;
    }
    int width = img->header->width;
    int height = img->header->height;
    int shift = countShift(img->header->width);
    fseek(file, img->header->offBits, SEEK_SET);
    for (int i = height - 1; i >= 0; i--){
        if ((int) fwrite(img->data[i], sizeof(pixel), width, file) != width){
            return 1;
        }
        for (int j = 0; j < shift; ++j)
            putc('\0', file);
    }
    return 0;
}

int crop(Bitmap *img, int xStart, int yStart, int width, int height){
    pixel **data = (pixel **)arrayConstructor(sizeof(pixel), height, width);
    if (!data){
        return -1;
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            data[i][j] = (img->data)[yStart + i][xStart + j];
        }
    }
    bmpHeader *header = headerConstructor(img->header, width, height);
    if (!header){
        arrayDestructor(data);
        return -1;
    }
    bmpReplacer(img, header, data);
    return 0;
}

int rotate(Bitmap *img){
    int widthRot = img->header->height;;
    int heightRot = img->header->width;
    pixel **data = (pixel **)arrayConstructor(sizeof(pixel), heightRot, widthRot);
    if (!data){
        return -1;
    }
    for (int i = 0; i < heightRot; ++i){
        for (int j = 0; j < widthRot; ++j){
            data[i][j] = img->data[widthRot - 1 - j][i];
        }
    }
    bmpHeader *header = headerConstructor(img->header, widthRot, heightRot);
    if (!header){
        arrayDestructor(data);
        return -1;
    }
    bmpReplacer(img, header, data);
    return 0;
}