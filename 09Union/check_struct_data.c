/*int 型, float 型, double 型の 3 つの値を持つような構造体 foo を定義し,
 foo で宣言した変数中の各値に割り当てられたアドレスを表示するようなプログラムを書きなさい.*/
#include<stdio.h>

typedef struct foo
{
    int i;
    float f;
    double d;
}F;

typedef union foo_u{
    int i;
    float f;
    double d;
}FU;

void main(){
    F f;
    printf("foo.i:%p.\nfoo.f:%p.\nfoo.d:%p.\n",&f.i, &f.f, &f.d);
}