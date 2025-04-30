#include<stdio.h>

void string_copy(char *p1,char *p2){
    
    while (*p1 != '\0')
    {
        *p2 = *p1;
        p1++;
        p2++;
    }

    *p2 = '\0' ;
}


int main(){
    char s1[1024];
    char s2[1024];
    printf("type the string1:");
    scanf("%s",s1);
    printf("type the string2:");
    scanf("%s",s2);
    char *p1 = &(s1[0]);
    char *p2 = &(s2[0]);

    string_copy(p1,p2);

    printf("copied s2: %s\n", s2);

    return 0;
}

