#include<stdio.h>

int main(){
    char s[8]="abcdefg";
    char *p = &(s[0]);
    
    for(int i = 0; i < sizeof(s) -1; i++){
        *p = *p - 32;
        printf("%s\n", s);
        p++;
    }
}