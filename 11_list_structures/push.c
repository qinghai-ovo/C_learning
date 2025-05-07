/*演習 push.c
新しいデータとリストの先頭のセルを指すポインタを受け取り, 
リストの先頭にセルを追加して, 
新しく先頭となったセルを指すポインタを返す 関数 push を定義しなさい.
main 関数と実行例
push.c:main

  main() {
    struct cell *plist;

    plist=NULL;
    plist = push(3,plist);
    plist = push(2,plist);
    plist = push(1,plist);

    printList(plist);
  }
% a.out
1 2 3
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
}