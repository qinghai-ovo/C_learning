/*int 型, float 型, double 型の 3 つの値を持つような共用体 bar を定義し, 
bar で宣言した変数中の各値に割り当てられたアドレスを表示するようなプログラムを書きなさい..*/
#include<stdio.h>

typedef struct foo
{
    int i;
    float f;
    double d;
}F;

typedef union bar{
    int i;
    float f;
    double d;
}BAR;

void main(){
    BAR bar;
    printf("bar.i:%p.\nbar.f:%p.\nbar.d:%p.\n",&bar.i, &bar.f, &bar.d);
}