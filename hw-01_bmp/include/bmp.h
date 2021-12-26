#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PIXEL_SIZE 3

#ifndef BMPHEADERFILE
#define BMPHEADERFILE

typedef struct{
    int x, y;
} pair;

typedef __int16_t WORD;

#pragma pack(push, 2)
typedef struct{
    WORD type;         
    int sizeFile;      
    int reserved;      
    int offBits;       
    int sizeHeader;          
    int width;         
    int height;        
    WORD planes;       
    WORD bitCount;     
    int compression;   
    int sizeImage;     
    int xPixPerInch; 
    int yPixPerInch; 
    int clrUsed;       
    int clrImportant;  
} bmpHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct{
    unsigned char r, g, b;
} pixel;
#pragma pack(pop)

typedef struct{
    bmpHeader *header;
    pixel **data;
} Bitmap;

void bmpDestructor(Bitmap *);

Bitmap *loadBitmap(const char *);

int saveBitmap(FILE *, Bitmap *);

int rotate(Bitmap *);

int crop(Bitmap *, int, int, int, int);

#endif