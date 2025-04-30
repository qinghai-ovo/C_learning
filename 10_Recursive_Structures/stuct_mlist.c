#include<stdio.h>
#include<string.h>

typedef struct mlist{
    char *str;
    int i;
    struct mlist *next; 
}MList;