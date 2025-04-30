#include<stdio.h>

int main(){
    int i ;
    char c ;
    float f ;

    int *p1;
    char *p2;


    printf( "i: %p\n" , &i );
    printf( "c: %p\n" , &c );
    printf("f: %p\n", &f);

    printf("p1size: %d\n",sizeof(p1));
    printf("p2size: %d\n",sizeof(p2));
    
}