/*前述の2分木において, 1つのitemと2つの副木を引数として取り, 
それらの副木を子供とする新しい item節を返す関数を定義しなさい. 
また, その関数を使って生成した木を表示する関数を定義しなさい.
main 関数と実行例
gene_btree.c: main

  main () {
    struct node *root;

    root = create_node(3,NULL,NULL);
    root = create_node(8,root,NULL);
    root = create_node(7,create_node(5,NULL,NULL), root);

    print_nodes (root);
  }
% a.out
( 7, ( 5, NULL, NULL ), ( 8, ( 3, NULL, NULL ), NULL ) )

%*/
#include<stdio.h>
#include<malloc.h>

typedef struct bintree
{
    int i;
    struct bintree *leftnode;
    struct bintree *rightnode;
}bintree;

bintree *create_node(int i, bintree *leftnode, bintree *rightnode){
    bintree *node = malloc(sizeof(bintree));
    node -> i = i;
    node -> leftnode = leftnode;
    node -> rightnode = rightnode;
    return node;
}

void print_node(bintree *root){
    if(root == NULL){
        printf("NULL");
        return;
    }
    printf("(%d", root -> i);
    printf(", ");
    print_node(root -> leftnode);
    printf(", ");
    print_node(root -> rightnode);
    printf(")");
}

void main(){
    bintree *root;
    
    root = create_node(3, NULL, NULL);
    root = create_node(8, root, NULL);
    root = create_node(7, create_node(5,NULL,NULL), root);

    print_node(root);
    printf("\n");
    free(root);
};