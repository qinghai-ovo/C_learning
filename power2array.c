#include<stdio.h>

void main(){
    int ary[10];

    for(int i = 0; i<=9; i++){
        ary[i] = i * i;
        printf("%d\n", ary[i]);
    }
}