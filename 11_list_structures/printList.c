/*リストの先頭のセルを指すポインタを受け取り, リストに格納されたデータを順に 表示する関数 printList を定義しなさい.
main 関数と実行例
printList.c:main

  main() {
    struct cell *pc1,*pc2,*pc3;

    pc1 = malloc(sizeof(struct cell));
    pc2 = malloc(sizeof(struct cell));
    pc3 = malloc(sizeof(struct cell));

    pc1->item = 1; pc1->next = pc2;
    pc2->item = 2; pc2->next = pc3;
    pc3->item = 3; pc3->next = NULL;

    printList(pc1);
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

int main(){
    List *pc1, *pc2, *pc3;
    pc1 = malloc(sizeof(List));
    pc2 = malloc(sizeof(List));
    pc3 = malloc(sizeof(List));

    pc1->i = 1; pc1->next = pc2;
    pc2->i = 2; pc2->next = pc3;
    pc3->i = 3; pc3->next = NULL;

    printlist(pc1);
    
    free(pc1);
    free(pc2);
    free(pc3);
    return 0;
}