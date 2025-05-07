/*演習 pop.c
リストの先頭のセルを指すポインタを受け取り, 先頭のセルを削除して, 新しく先頭となったセルを指すポインタを返す関数 pop を定義しなさい.
不要になったセルは, free すること.
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct List
{
    int i;
    struct List *next;
}List;

void printlist(List *prt){
    if(prt == NULL) {
        printf("\n");
        return;
    }
    printf("%d ",prt -> i);
    printlist(prt -> next);
}

List *pop(List *plist){
    if(plist == NULL){
        return plist;
    }
    List *new;
    new = plist -> next;
    free(plist); 
    return new;
};

List *push(int n, List *plist){
    List *node = malloc(sizeof(List)); 
    node -> i = n;
    node -> next = plist;
    return node;
}

int main(){
    List *plist;

    plist = NULL;
    plist = push(3,plist);
    plist = push(2,plist);
    plist = push(1,plist);

    printlist(plist);

    plist = pop(plist);
    printlist(plist);
}