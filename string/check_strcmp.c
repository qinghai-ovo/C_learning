#include <stdio.h>
#include <string.h>

void main () {
    char string1[4] = "abc";
    char string2[4] = "def";
    int i;

    i = strcmp( string1 , string1 );
    printf( "[%s] [%s] %d\n" , string1 , string1 , i );

    i = strcmp( string1 , string2 );
    printf( "[%s] [%s] %d\n" , string1 , string2 , i );

    i = strcmp( string2 , string1 );
    printf( "[%s] [%s] %d\n" , string2 , string1 , i );
  }