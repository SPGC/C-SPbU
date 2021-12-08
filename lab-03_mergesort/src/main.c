#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mergesort.h"


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
        free(array);
        return -1;
    }
    switch (elementSize)
    {
    case sizeof(int):
        for(int i = 0; (size_t) i < arraySize; i++){
            ((int*) array)[i] = atoi(argv[i + 2]);
        }
        if(mergeSort(array, arraySize, elementSize, integerComparator) == -1){
            printf("Error: memory allocation failed\n");
            return -1;
        }
        for(int i = 0; (size_t) i < arraySize - 1; i++){
            printf("%d ", ((int*) array)[i]);
        }
        printf("%d", ((int*) array)[arraySize - 1]);
        printf("\n");
        free(array);
    return 0;
    case sizeof(char):
        for(int i = 0; (size_t) i < arraySize; i++){
            ((char*) array)[i] = argv[i + 2][0];
        }
        if(mergeSort(array, arraySize, elementSize, charComparator) == -1){
            printf("Error: memory allocation failed\n");
            return -1;
        }
        for(int i = 0; (size_t) i < arraySize - 1; i++){
            printf("%c ", ((char*) array)[i]);
        }
        printf("%c", ((char*) array)[arraySize - 1]);
        printf("\n");
        free(array);
    return 0;
    case sizeof(char*):
        for(int i = 0; (size_t) i < arraySize; i++){
            ((char**) array)[i] = argv[i + 2];
        }
        if(mergeSort(array, arraySize, elementSize, stringComparator) == -1){
            printf("Error: memory allocation failed\n");
            return -1;
        }
        for(int i = 0; (size_t) i < arraySize - 1; i++){
            printf("%s ", ((char**) array)[i]);
        }
        printf("%s", ((char**) array)[arraySize - 1]);
        printf("\n");
        free(array);
    return 0;
    }
}