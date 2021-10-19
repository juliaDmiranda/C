#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char str[20] = "123 oia qui";

    char *p;
    puts(str);
    p = strtok(str, " ");

    printf("primeiro: %s \n depois: %s", p, str);
    p = strtok(NULL, "");
    printf("primeiro: %c \n depois: %s", p[0], str);

    return 0;
}
