/*
演習 memberlist2.c では, 登録できる文字列の最大数が 100 を超えないことを仮定している.
実行したときに, 最初に登録数を入力するようにし, その数だけデータの領域を確保するように改造しなさい.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **Data;
int dataIndex;

void main() {
    char buffer[1024];
    int i,n = 0;
    
    while(!(n > 0 && n <= 100)){
        if(n > 100) printf("Input Error!\n");
        printf("Input the number you need to register((<=100)):\n");
        scanf("%d", &n);
    }
    
    Data = malloc(n * sizeof(*Data));
    
    dataIndex = 0;

    printf("Input %d strings:\n", n);
    while( dataIndex < n ) {
        scanf( "%s" , buffer );
        if ( strcmp( "end" , buffer ) == 0 ) break;
        
        size_t len = strlen(buffer) + 1;

        Data[dataIndex] = malloc(len);

        strcpy(Data[dataIndex], buffer);

        dataIndex = dataIndex + 1;
        if(dataIndex < n) printf("Input next string(%d left):\n",n - dataIndex);
    }

    printf( "----\n" );

    for ( i = 0 ; i < dataIndex ; i++ ) {
      printf( "%s\n" , Data[i] );
      free(Data[i]);
    }
    free(Data);
  }