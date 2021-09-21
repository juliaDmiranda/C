#include <stdio.h>
#include <stdlib.h>

int main()
{
    char desenho[2][2];
    char paredes = 220;
    char texturaparede[10];
    char janelasuper[3]={201,205,187};

    char janelainfer[3]={200,205,188};

    for (int i = 0; i < 10; i++)
    {
        texturaparede[i] = 176;
    }

    printf("_________________________");
    printf("\n|");
    for (int i = 0; i < 10; i++)
    {
        if (i != 5)
            printf("%c", texturaparede[i]);
        else if (i == 5)
            printf("%s",janelasuper);
    }

    printf("|\t%c\t%c",244, 244);

    printf("\n|");
    
    for (int i = 0; i < 7; i++)
    {
        if (i != 5)
            printf("%c", texturaparede[i]);
        else if (i == 5)
            printf("%c%c%c",janelainfer[0],janelainfer[1],janelainfer[2]);

    }

    printf("|      %c      %c", 244, 244);
    printf("\n|%s|    %c     %c", texturaparede, 244, 244);
    printf("\n|%s|", texturaparede);

    printf("___| |___| |____");
    // printf("\n|\n|");
}