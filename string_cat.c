#include<stdio.h>
#include<stdlib.h>

void string_copy(char *p1,char *p2){   
    while (*p1 != '\0')
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
    char *s3;
    s1 = malloc(sizeof(char[1024]));
    s2 = malloc(sizeof(char[1024]));
    printf("Input the string1:");
    scanf("%s",s1);
    printf("Input the string2:");
    scanf("%s",s2);
    s3 = malloc(sizeof(char[string_legth(s1)+string_legth(s2)]));
    string_copy(s1,s3);
    string_copy(s2,s3+string_legth(s1));
    free(s1);
    free(s2);

    printf("s3: %s\n", s3);
    free(s3);


    return 0;
}

