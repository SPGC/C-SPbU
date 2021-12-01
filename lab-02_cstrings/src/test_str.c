#include "str.h"
#include <assert.h>
#include "test_str.h"
#include <string.h>
#define SIZE_OF_STRINGS 20


void test_strcpy(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    // Базовая проверка, что всё работает
    assert(strcmp(my_strcpy(testString1, testString4), testString4) ==  0);
    assert(strcmp(my_strcpy(testString1, testString2), testString2) ==  0);
    assert(strcmp(my_strcpy(testString1, testString3), testString3) ==  0);    

    //Граничные случаи
    assert(strcmp(my_strcpy(empty, ""), "") ==  0); // Пустая в пустую
    assert(strcmp(my_strcpy(testString1, ""), "") ==  0); // В копируемой строке 0 символов
    assert(strcmp(my_strcpy(testString1, "CirillaZoltanChivay"), "CirillaZoltanChivay") ==  0); // В копируемой строке максимальное количество символов
}

void test_strlen(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    assert(my_strlen(empty) == 0);
    assert(my_strlen(testString3) == 5);
    assert(my_strlen(testString1) == 6);
    assert(my_strlen(testString4) == 13);
}

void test_strcmp(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    // Базовая проверка, что всё работает
    assert(my_strcmp(testString1, testString3) < 0); 
    assert(my_strcmp(testString4, testString1) > 0);  

    // Граничные случаи 
    assert(my_strcmp(empty, "") == 0); // Пустая с пустой
    assert(my_strcmp(testString4, testString4) == 0); // Строка сама с собой
    assert(my_strcmp(testString4, "Zoltan Chivay") == 0); // Строка с дополнительными зарезервированными местами и без
    assert(my_strcmp(testString1, testString2) > 0); // Проверяем, что работает в обе стороны + проверка того, что более длинная строка может оказаться меньше
    assert(my_strcmp(testString2, testString1) < 0);
    assert(my_strcmp(testString1, "Gerald") > 0); // Изменён суффикс
    assert(my_strcmp(testString1, "Heralt") < 0); // Изменён префикс
    assert(my_strcmp(testString1, "GeRalt") > 0); // Изменена буква в середине
    
}

void test_strcat(){
    char testString0[SIZE_OF_STRINGS] = "Geralt";
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    // Базовая проверка, что всё работает
    assert(strcmp(my_strcat(testString1, testString4), "GeraltZoltan Chivay") ==  0);
    my_strcpy(testString1, testString0);
    assert(strcmp(my_strcat(testString1, testString2), "GeraltCirilla") ==  0);
    my_strcpy(testString1, testString0);
    assert(strcmp(my_strcat(testString1, testString3), "GeraltRoach") ==  0);    
    my_strcpy(testString1, testString0);

    // Граничные случаи
    assert(strcmp(my_strcat(empty, ""), "") ==  0); // Пустая дополняется пустой
    assert(strcmp(my_strcat(testString1, ""), "Geralt") ==  0); // Непустая строка дополняется пустой
    assert(strcmp(my_strcat(testString1, "Zoltan Chivay."), "GeraltZoltan Chivay.") ==  0); // Строка дополняется до максимального объявленного размера
}