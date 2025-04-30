#include<stdio.h>

void foo(int *p){
    printf("foo: received i:%d\n", *p);
    *p = 222;
    printf("foo: modified i:%d\n", *p);
}

int main(){
    int i  = 100;
    int *p = &i;

    printf("main: initialized i:%d\n", i);
    foo(p);
    printf("main: after foo i:%d\n", i);

    return 0;
}