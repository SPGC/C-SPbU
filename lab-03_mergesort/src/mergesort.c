#include "mergesort.h"
#include <stdlib.h>

// Производит слияние массивов left и right в массив resultArray. leftSize, rightSize - длинны соответствующих массивов
<<<<<<< HEAD
// elementSize - размер элементов массива в байтах, cmp - метод сравнения двух элементов.
=======
// elementSize - размер элементов массива в байтах, cmp - метод сравнения двух элементов
>>>>>>> c902e38e9bcf68d72fe29e593cc24b8e6e3f5ddd
void merge(void *left, void *right, size_t leftSize, size_t rightSize, size_t elementSize, comparator cmp, void *resultArray){
    int leftPointer = 0;
    int rightPointer = 0;
    while((size_t) leftPointer < leftSize || (size_t) rightPointer < rightSize){
        if((size_t) leftPointer < leftSize){
            if((size_t) rightPointer < rightSize){
                if(cmp(left + leftPointer * elementSize, right + rightPointer * elementSize) >= 0){
                    elementsCpy(right + rightPointer * elementSize, resultArray + (leftPointer + rightPointer) * elementSize, elementSize);
                    rightPointer++;
                } else {
                    elementsCpy(left + leftPointer * elementSize, resultArray + (leftPointer + rightPointer) * elementSize, elementSize);
                    leftPointer++;
                }
            } else {
                elementsCpy(left + leftPointer * elementSize, resultArray + (leftPointer + rightPointer) * elementSize, elementSize);
                leftPointer++;
            }
        } else {
            elementsCpy(right + rightPointer * elementSize, resultArray + (leftPointer + rightPointer) * elementSize, elementSize);
            rightPointer++;
        }
    }
}

// Сортировка слиянием массива array. arraySize - длинна массива, elementSize - размер элементов массива в байтах
// cmp - метод сравнения двух элементов
int mergeSort(void* array, size_t arraySize, size_t elementSize, comparator cmp){
    if(arraySize < 2){
        return 0;
    }
    size_t leftsize = arraySize / 2;
    size_t rightsize = arraySize - leftsize;
    void *left = array;
    void *right = array + leftsize * elementSize;
    mergeSort(left, leftsize, elementSize, cmp);
    mergeSort(right, rightsize, elementSize, cmp);
    void* resultArray = malloc(arraySize * elementSize);
    if(resultArray == NULL){
        free(resultArray);
        return -1;
    }
    merge(left, right, leftsize, rightsize, elementSize, cmp, resultArray);
    elementsCpy(resultArray, array, arraySize * elementSize);
    free(resultArray);
    return 0;
}

<<<<<<< HEAD
// Копирует element1 в element2. elementSize - размер копируемого куска
=======
// Копирует element1 в element2
>>>>>>> c902e38e9bcf68d72fe29e593cc24b8e6e3f5ddd
void elementsCpy(void* element1, void* element2, size_t element1Size){
    char* pointerOnElement1 = element1;
    char* pointerOnElement2 = element2;
    for(int i = 0; (size_t) i < element1Size; i++){
        *(pointerOnElement2 + i) = *(pointerOnElement1 + i);
    }
}