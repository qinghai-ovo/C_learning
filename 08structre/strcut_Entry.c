/*名簿を作成したい. 一人分のデータとして, 学籍番号(整数値)と名前(文字列)を 
考える. このような一人分のデータを表す構造体を定義しなさい.*/

#include<stdio.h>
#include<string.h>

typedef struct student_directory
{
    int id_number;
    char name[50];
    char gender[10];
    int phone_number; 
};
 