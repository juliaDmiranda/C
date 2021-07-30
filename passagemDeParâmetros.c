#include<stdarg.h>
#include<stdlib.h>
#include<stdio.h>

int funcao(int k, ...){
    va_list args;
	va_start(args, k);
	
    int proxi = va_arg(args, int);


    int a = k + proxi;

    proxi = va_arg(args, int);


    a += proxi;
	va_end(args);
    return a;
}

int main(){
   int a = funcao(1,2 , 3);
    
   printf("%d", a);
}
