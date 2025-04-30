#include<stdio.h>

void caps(char *p){
    if(*p >= 'a' && *p <= 'z'){
        *p = *p - 32;
    }else if(*p >= 'A' && *p <= 'Z'){
        *p = *p + 32; 
    }
}


int main(){
    char s[1024];
    scanf("%s",s);
    char *p = &(s[0]);
    while (*p != '\0')
    {
        caps(p);
        printf("%s\n",s);
        p++;
    }

}

