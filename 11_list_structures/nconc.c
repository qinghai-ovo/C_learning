/*nconc.c
2つのリストの先頭を指すポインタをそれぞれ受け取り, それらのリストを繋げ, 繋げたリストの先頭を返す関数 nconc を定義しなさい.

main 関数と実行例
nconc.c:main

  main() {
    struct cell *pl1,*pl2,*res;

    pl1=NULL;
    pl1 = push(3,pl1);
    pl1 = push(2,pl1);
    pl1 = push(1,pl1);

    pl2=NULL;
    pl2 = push(30,pl2);
    pl2 = push(20,pl2);
    pl2 = push(10,pl2);

    printList(pl1);
    printList(pl2);

    res = nconc(pl1,pl2);
    printList(res);
    printList(pl1);
  }
% a.out
1 2 3
10 20 30
1 2 3 10 20 30
1 2 3 10 20 30

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

int main(){
    List *plist,*plist2,*res;

    plist = NULL;
    plist = push(3,plist);
    plist = push(2,plist);
    plist = push(1,plist);

    printlist(plist);

    plist2 = NULL;
    plist2 = push(30,plist2);
    plist2 = push(20,plist2);
    plist2 = push(10,plist2);

    printlist(plist2);

    res = conc(plist,plist2);
    printlist(res);
}