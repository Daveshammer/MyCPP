#include<stdio.h>

int main()
{
    char str[20]= "abcdefg";
    char *s=str;
    // strcpy(s,"hello");
    s="hello";
    str[3]='\0';
    printf("%s",str);

    return 0;
}   