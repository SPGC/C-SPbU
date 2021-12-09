#include <stdlib.h>

#include "mergesort.h"


// Копирует область памяти sourcePointer в область памяти distanationPointer. 
// elementSize - размер копируемой области
void elementsCpy(void* sourcePointer, void* distanationPointer, size_t element1Size){
    char* pointerOnElement1 = sourcePointer;
    char* pointerOnElement2 = distanationPointer;
    for(int i = 0; (size_t) i < element1Size; i++){
        pointerOnElement2[i] = pointerOnElement1[i];
    }
}

// Производит слияние массивов left и right в массив resultArray. 
// leftSize, rightSize - длинны соответствующих массивов
// elementSize - размер элементов массива в байтах, 
// cmp - метод сравнения двух элементов.
void merge(void *left, void *right, size_t leftSize, size_t rightSize,
           size_t elementSize, comparator cmp, void *resultArray){
    char *leftPointer = left;
    char *rightPointer = right;
    char *resultArrayPointer = resultArray;
    while(resultArrayPointer < 
          (char *)resultArray + elementSize * (rightSize + leftSize)){
        if((leftPointer < (char *)left + leftSize * elementSize) &&
         (rightPointer >= (char *)right + rightSize * elementSize || 
         cmp(leftPointer, rightPointer) <= 0)){
            elementsCpy(leftPointer, resultArrayPointer, elementSize);
            leftPointer += elementSize;
        } else {
            elementsCpy(rightPointer, resultArrayPointer, elementSize);
            rightPointer += elementSize;
            }
        resultArrayPointer += elementSize;

    }
}

// Сортировка слиянием массива array. arraySize - длинна массива, 
// elementSize - размер элементов массива в байтах
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
        return -1;
    }
    merge(left, right, leftsize, rightsize, elementSize, cmp, resultArray);
    elementsCpy(resultArray, array, arraySize * elementSize);
    free(resultArray);
    return 0;
}
