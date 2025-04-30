#include<stdio.h>

int main(){
    char s[30];
    int i;

    for (i = 0; i < 26; i++){
        s[i] ='z' - i;
    }

    printf("%s\n", s);
}