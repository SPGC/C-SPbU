#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mergesort.h"

typedef void (*printer)(const void *);  
typedef void (*parser)(void *, size_t, const char **); 

// Метод сравнения для int
int integerComparator(const void *element1, const void *element2){
    return *(int*) element1 - *(int*) element2;
}

// Метод сравнения для char
int charComparator(const void *element1, const void *element2){
    return *(char*) element1 - *(char*) element2;
}

// Метод сравнения для string
int stringComparator(const void *element1, const void *element2){
    return strcmp(*(char**) element1, *(char**) element2);
}

// Метод печати int
void printInteger(const void *pointer){
    printf("%d", *(int*) pointer );
}

// Метод печати char
void printChar(const void *pointer){
    printf("%c", *(char*) pointer );
}

// Метод печати string
void printString(const void *pointer){
    printf("%s", *(char**) pointer );
}

// Метод, парсящий массив строк parsingArray в массив int parsedArray
// arraySize - размер массива parsingArray
void parseArrToInts(void *parsedArray, size_t arraySize, char **parsingArray){
    for(int i = 0; (size_t) i < arraySize; i++){
            ((int*) parsedArray)[i] = atoi(parsingArray[i]);
        }
}

// Метод, парсящий массив строк parsingArray в массив char parsedArray
// arraySize - размер массива parsingArray
void parseArrToChar(void *parsedArray, size_t arraySize, char **parsingArray){
    for(int i = 0; (size_t) i < arraySize; i++){
            ((char*) parsedArray)[i] = parsingArray[i][0];
        }
}

// Метод, копирующий массив строк sourceArray в массив distArray
// arraySize - размер массива sourceArray
void cpyStringArray(void *distArray, size_t arraySize, char **sourceArray){
    for(int i = 0; (size_t) i < arraySize; i++){
            ((char**) distArray)[i] = sourceArray[i];
        }
}

// Метод, сортирующий массив array и выводящий полученное значение в терминал. 
// arraySize - размер входного массива
// elemetSize - размер элемента массива, 
// comparator - метод сравнения 2-х элементов
// printer - метод вывода элемента в терминал
int sortAndPrint(void *array, size_t arraySize, size_t elementSize, 
                  comparator comparator, printer printer){
    if(mergeSort(array, arraySize, elementSize, comparator) == -1){
        printf("Error: memory allocation failed\n");
        return -1;
    }
    for(int i = 0; (size_t) i < arraySize; i++){
        if(i){
            printf(" ");
        }
        printer(array + i * elementSize);
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("\n");
        return 0;
    }
    size_t elementSize; 
    if(strcmp(argv[1], "int") == 0){
        elementSize = sizeof(int);
    } else if (strcmp(argv[1], "char") == 0){
        elementSize = sizeof(char);
    } else if (strcmp(argv[1], "str") == 0){
        elementSize = sizeof(char*);
    } else {
        printf("Wrong input\n");
        return -1;
    }
    size_t arraySize = argc - 2;
    void *array = malloc(elementSize * arraySize);
    if(array == NULL){
        printf("Error: memory allocation failed\n");
        return -1;
    }
    int succesFlag;
    switch (elementSize)
    {
    case sizeof(int):
        parseArrToInts(array, arraySize, argv + 2);
        succesFlag = sortAndPrint(array, arraySize, elementSize, integerComparator, printInteger);
        break;
    case sizeof(char):
        parseArrToChar(array, arraySize, argv + 2);
        succesFlag = sortAndPrint(array, arraySize, elementSize, charComparator, printChar);
        break;
    case sizeof(char*):
        cpyStringArray(array, arraySize, argv + 2);
        succesFlag = sortAndPrint(array, arraySize, elementSize, stringComparator, printString);  
        break;
    }
    free(array);
    return succesFlag;
}