#include<stdio.h>
int main()
{
    FILE* file=fopen("usernames.csv","r");
    char str[1000];
    while(fgets(str,1000,file)!=NULL)
        printf("%s",str);
}