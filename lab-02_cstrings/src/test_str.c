#include "str.h"
#include <assert.h>
#include <test_str.h>
#include <string.h>
#define SIZE_OF_STRINGS 40


void test_strcpy(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    assert(strcmp(my_strcpy(empty, ""), "") ==  0);
    assert(strcmp(my_strcpy(testString1, testString4), testString4) ==  0);
    assert(strcmp(my_strcpy(testString1, testString2), testString2) ==  0);
    assert(strcmp(my_strcpy(testString1, testString3), testString3) ==  0);    
    assert(strcmp(my_strcpy(testString1, ""), "") ==  0);
}

void test_strlen(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    assert(my_strlen(empty) == 1);
    assert(my_strlen(testString3) == 6);
    assert(my_strlen(testString1) == 7);
    assert(my_strlen(testString4) == 14);
}

void test_strcmp(){
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";
    
    assert(my_strcmp(empty, "") == 0);
    assert(my_strcmp(testString4, testString4) == 0);
    assert(my_strcmp(testString4, testString1) > 0);
    assert(my_strcmp(testString1, testString2) > 0);
    assert(my_strcmp(testString1, testString3) < 0);
    assert(my_strcmp(testString2, testString1) < 0);
}

void test_strcat(){
    char testString0[SIZE_OF_STRINGS] = "Geralt";
    char testString1[SIZE_OF_STRINGS] = "Geralt";
    char testString2[SIZE_OF_STRINGS] = "Cirilla";
    char testString3[] = "Roach";
    char testString4[SIZE_OF_STRINGS] = "Zoltan Chivay";
    char empty[] = "";

    assert(strcmp(my_strcat(empty, ""), "") ==  0);
    assert(strcmp(my_strcat(testString1, testString4), "GeraltZoltan Chivay") ==  0);
    my_strcpy(testString1, testString0);
    assert(strcmp(my_strcat(testString1, testString2), "GeraltCirilla") ==  0);
    my_strcpy(testString1, testString0);
    assert(strcmp(my_strcat(testString1, testString3), "GeraltRoach") ==  0);    
    my_strcpy(testString1, testString0);
    assert(strcmp(my_strcat(testString1, ""), "Geralt") ==  0);
}