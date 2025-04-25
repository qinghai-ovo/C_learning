#include<stdio.h>
#include<stdlib.h>

void string_conc(char *p1,char *p2){   
    while (*p2 != '\0')
    {
        *p2 = *p1;
        p1++;
        p2++;
    }
    *p2 = '\0' ;
}

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
    char *s1;
    char *s2;
    s1 = malloc(sizeof(char[1024]));
    printf("Input the string1:");
    scanf("%s",s1);
    s2 = malloc(sizeof(char[string_legth(s1)]));
    string_copy(s1,s2);

    printf("copied s2: %s\n", s2);

    free(s1);
    free(s2);
    return 0;
}

