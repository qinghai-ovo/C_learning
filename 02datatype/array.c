#include<stdio.h>

int main(){
    char s[10];
    int i;

    for (i = 0; i < 9; i++){
        s[i] ='A' + i;
    }
    s[9] = 0;

    printf("%s\n", s);
}