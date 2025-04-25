#include<stdio.h>
#include<stdlib.h>

int main(){
    int *p;

    p = malloc(sizeof(int));
    printf("Input an integer:\n");
    scanf("%d", p);
    printf("%d\n", *p);
    free(p);

    return 0;
}

