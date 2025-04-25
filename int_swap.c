#include<stdio.h>

void int_swap(int *p1, int*p2){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


int main(){
    int a,b;
    printf("before: a = ");
    scanf("%d", &a);
    printf("before: b = ");
    scanf("%d", &b);
    int *p1 = &a;
    int *p2 = &b;

    int_swap(p1,p2);

    printf("after: a = %d, b = %d\n", a, b);

    return 0;
}

