#include<stdio.h>
#include"mathbasic.h"

int main(){
    printf("\n%d + %d = %d",1,2,som(1,2));
    printf("\n%d + %d = %d",1,2,sub(1,2));
    printf("\nSomato'rio [%d,%d] = %d",1,3,somIntervalo(1,3));
    return 0;
}