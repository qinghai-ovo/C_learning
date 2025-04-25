#include<stdio.h>

void foo(int i){
    printf("foo: received i:%d\n", i);
    i = 222;
    printf("foo: modified i:%d\n", i);
}

int main(){
    int i  = 100;
    int *p = &i;

    printf("main: initialized i:%d\n", i);
    foo(i);
    printf("main: after foo i:%d\n", i);

    return 0;
}