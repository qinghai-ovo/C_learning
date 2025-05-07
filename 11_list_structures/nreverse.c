/*演習 reverse.c
リストの先頭を指すポインタを受け取り, そのリストを逆順に並べ変えたリストを作り, 作ったリストの先頭を返す関数 reverse を定義しなさい.

main 関数と実行例
reverse.c:main

  main() {
    struct cell *pl,*res;

    pl=NULL;
    pl = push(3,pl);
    pl = push(2,pl);
    pl = push(1,pl);

    printList(pl);

    res = reverse(pl);
    printList(res);
  }
% a.out
1 2 3
3 2 1

%
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
}

List *push(int n, List *plist){
    List *node = malloc(sizeof(List)); 
    node -> i = n;
    node -> next = plist;
    return node;
}

List *next(List *plist){
    return (plist -> next);
}

List *conc(List *plist1, List *plist2){
    if(plist1 == NULL) {
        return plist2;
    } 
    List *p = plist1;
    while (p -> next != NULL)
    {
        p = p -> next;
    }
    p -> next = plist2;
    return plist1;
}

List *reverse(List *plist){
    List *prev = NULL;
    List *cur = plist;
    while (cur != NULL)
    {
        List *next = cur -> next;
        cur -> next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

int main(){
    List *plist,*res;

    plist = NULL;
    plist = push(3,plist);
    plist = push(2,plist);
    plist = push(1,plist);
    printlist(plist);

    res = reverse(plist);
    printlist(res);
    printlist(plist);
}