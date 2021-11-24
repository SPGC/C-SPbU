#include <str.h>

char *my_strcpy(char * restrict s1, const char * restrict s2){
    int i = -1;
    do {
        i++;
        *(s1+i) = *(s2+i);
    
    } while (*(s2+i) != '\0');
    return s1;
}

size_t my_strlen( const char *s) {
    const char *endOfString = s;
    while (*endOfString != '\0') {
        endOfString++;
    }
    return endOfString - s;
}

char *my_strcat(char * restrict s1, const char * restrict s2){
    size_t endOfString = my_strlen(s1);
    my_strcpy(s1+endOfString, s2);
    return s1;
}

int my_strcmp(const char *s1, const char *s2) 
{   
    int i = 0;
    while((*(s1 + i) == *(s2 + i)) && (*(s1 + i) != '\0') && (*(s2 + i) != '\0')){
        i++;
    }
    return *(s1+i) - *(s2+i);
}