/*
演習 memberlist.c では, 文字列の長さが最大でも 30文字を超えないことを仮定した.
この最大文字数を 1024文字としたい.
しかし, すべての文字列に 1024 文字分の領域を割り当てるのは, 短い文字列を登録する場合に無駄である.
そこで, 入力された文字列の長さに対応してメモリを確保することで, 無駄なメモリを使わないように改良しなさい.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *Data[100];
int dataIndex;

void main() {
    char buffer[1024];
    int i;

    dataIndex = 0;

    while( 1 ) {
        scanf( "%s" , buffer );
        if ( strcmp( "end" , buffer ) == 0 ) break;
        
        size_t len = strlen(buffer) + 1;

        Data[dataIndex] = malloc(len);

        strcpy(Data[dataIndex], buffer);

        dataIndex = dataIndex + 1;
    }

    printf( "----\n" );

    for ( i = 0 ; i < dataIndex ; i++ ) {
      printf( "%s\n" , Data[i] );
      free(Data[i]);
    }
  }