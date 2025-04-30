#include <stdio.h>
#include <string.h>

void main () {
    char string1[8] = "abcdefg";
    char string2[4] = "ABC";

    printf( "string1:[%s]\n" , string1 );
    printf( "string2:[%s]\n" , string2 );

    strcpy( string1 , string2 );
    printf( "string1:[%s]\n" , string1 );
    printf( "string2:[%s]\n" , string2 );
  }