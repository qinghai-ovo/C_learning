#include<stdio.h>

void main(){
    char s[50];
    int a,b;

    printf( "Input String> ");
    scanf("%s%d%d", s, &a, &b);
    char temp = s[a-1];
    s[a-1] = s[b-1];
    s[b-1] = temp;
    printf( "%s\n",s);
}
