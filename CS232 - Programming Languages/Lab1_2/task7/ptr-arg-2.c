#include <stdio.h>

void swap(char **, char**);

int main() {
    char *str1 = "hello";
    char *str2 = "world";
    
    printf("BEFORE SWAP: str1 = %s and str2 = %s\n", str1, str2);
    
    swap(&str1, &str2);
    
    printf("AFTER SWAP: str1 = %s and str2 = %s\n", str1, str2);
}

void swap(char **n1, char **n2) {
    char *temp;
    
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
