#include<stdio.h>
#include<stdlib.h>

void main(){
    int number;
    char buffer[16];

    scanf("%s", buffer);
    number = atoi(buffer);
    printf("%d\n", number);
}