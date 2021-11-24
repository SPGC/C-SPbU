#include <str.h>

char *my_strcpy(char * restrict s1, const char * restrict s2){
    int i = -1;
    while((*(s1 + ++i) = *s2++));
    return s1;
}

size_t my_strlen( const char *s) {
    int sizeOfString = 0;
    while(*(s + sizeOfString++));
    return sizeOfString;
}

char *my_strcat(char * restrict s1, const char * restrict s2){
    size_t endOfString = my_strlen(s1)-1;
    my_strcpy(s1 + endOfString, s2);
    return s1;
}

int my_strcmp(const char *s1, const char *s2) {   
    while((*s1++ == *s2++) && *(s1 - 1));
    return *(s1 - 1) - *(s2 - 1);
}