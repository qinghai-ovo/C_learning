#include<stdio.h>

int string_legth(char *p){
    int length = 0;
    while (*p != '\0')
    {
        length++;
        p++;
    }
    return length;
}

int main(){
    char s[1024];
    printf("type the string:");
    scanf("%s",s);
    char *p = &(s[0]);
    
    printf("string_length is :%d\n", string_legth(p));
    
    return string_legth(p);
}

