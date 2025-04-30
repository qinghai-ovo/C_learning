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
    char tmp[1024];
    char *s1;
    printf("Input string:\n");
    while(scanf("%s", tmp) != EOF){
        s1 = malloc(sizeof(char) * string_legth(tmp));
        string_copy(tmp,s1);
        printf("Input is: %s\nInput string or Input 'Ctrl + D to end\n", s1);
        free(s1);
    }


    return 0;
}

