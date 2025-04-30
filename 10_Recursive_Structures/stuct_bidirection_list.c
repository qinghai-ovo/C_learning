#include<stdio.h>

typedef struct bidirection_list{
    struct BLIST *pre;
    int i;
    struct BLIST *next; 
}BLIST;