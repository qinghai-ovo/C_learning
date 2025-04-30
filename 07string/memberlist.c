/*入力された複数の文字列を扱うプログラム (例えば名簿のようなもの) を作ろうとして, 手始めに以下のようなプログラムを書いた.
ところが, 期待した動作をしない. なぜか.
理由を述べた上で, プログラムが正しく動くように改良しなさい.
そのとき, 各文字列は最大でも 30文字を超えないことを仮定してよい.
  #include <stdio.h>
  #include <string.h>

  char *Data[100];
  int dataIndex;

  main() {
    char buffer[1024];
    int i;

    dataIndex = 0;

    while( 1 ) {
      scanf( "%s" , buffer );
      if ( strcmp( "end" , buffer ) == 0 ) break;

      Data[dataIndex] = buffer;

      dataIndex = dataIndex + 1;
    }

    printf( "----\n" );

    for ( i = 0 ; i < dataIndex ; i++ ) {
      printf( "%s\n" , Data[i] );
    }
  }
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