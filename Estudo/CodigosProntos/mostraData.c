#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main () {
    struct tm tempo;
    time_t tempo_Seg;

    time(&tempo_Seg);
    tempo = *localtime(&tempo_Seg);

    printf(" Agora sao %02d : %02d : %02d \n Dia %d /%d / %d ",
    tempo.tm_hour,tempo.tm_min,tempo.tm_sec,tempo.tm_mday,tempo.tm_mon+1,tempo.tm_year+1900);

}