#include<stdio.h>

int main(){
    char s1[1024];
    char s2[1024];

    scanf("%s %s",s1,s2);

    char *p1 = &(s1[0]);
    char *p2 = &(s2[0]);
    
    while (*p1 != '\0'){
        p1++;
    }
    
    while(*p2 != '\0'){
        *p1 = *p2;
        p1++;
        p2++;
    }
    printf("%s\n",s1);
}

