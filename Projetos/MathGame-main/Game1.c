#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <windows.h>
const char* operations[3] = {"SUM","SUBTRACTION","MULTIPLICATION"};
const char  signals[3] = {'+','-','*'};
int scores = 0;
int resp = 1;
int result,yourans;

#define RESTART(){scores=0;}
#define RIGHTANS(){scores+=10;}

typedef struct{
    int value1,value2;
    int resp;
    int level;
}MATHGAME;

void SUM(int v1,int v2){result = v1+v2;}
void SUBTRACTION(int v1,int v2){result = v1-v2;}
void MULTIPLICATION(int v1,int v2){result = v1*v2;}

///Function to show the actual scores for the user
void SHOW_SCORES(){
    printf("\n\n\t\t________________________________________________________\n\n");
                printf("\t\t\t\t\tSCORES : %d",scores);
    printf("\n\n\t\t________________________________________________________\n\n");
}

///Function that show users the messeges asking if they want to quit the game or continues
///It's just the messeges for not  over word  the function MENU
void ASK_NEWGAME(){
        printf("\n\nWant a new game?\n1 - YES\t0 - NO\n\n");
        scanf("%d",&resp);
        system("cls");
        if(resp==0){
            printf("\n\nAre you sure about it?\n\n1 - QUIT\t2 - GO BACK\n");
            scanf("%d",&resp);
            if(resp==1)
                resp=0;
        }
}

void CHECK_ANS(int result){
    if(result == yourans){
        RIGHTANS();
        printf("\n\nRIGHT ANSWER!!");
        printf("\n\n+ 10");
        printf("\n\nKeep going :)");
        Sleep(1);
    }
    else{
        printf("\n\nWRONG ANSWER!!");
        printf("\n\n+ 0");
        printf("\n\nDON'T GIVE UP :)");
    }
    Sleep(1);

    system("cls");
    SHOW_SCORES();
}

void CHOOSE_OPERATION(int v1,int v2){
    int op;
    printf("\n\nYour operation is...\n\n");
    srand(time(NULL));
    op = rand() % 2;
    Sleep(1); 
    printf("\n\n%s!!!!\n\n",operations[op]);
    Sleep(1); 
    system("cls");
    switch (op)
    {
    case 0:
        printf("Your question\n%d + %d\n>  ",v1,v2);
        scanf("%d",&yourans);
        SUM(v1,v2);

        break;

    case 1:
        printf("Your question\n%d - %d\n>  ",v1,v2);
        scanf("%d",&yourans);
        SUBTRACTION(v1,v2);
    break;
    
    case 2:
        printf("Your question\n%d * %d\n>  ",v1,v2);
        scanf("%d",&yourans);
        MULTIPLICATION(v1,v2);
    break;
    
    default:
            printf("Unexpected result :( Sorry, we may restart your game...\n\n");
        break;
    }
    printf("\n\nThe result of %d %c %d is",v1,signals[op],v2);
    for (int i = 0; i < 5; i++){
        printf(".");
        Sleep(1);
    }
    printf("\n%d",result);

    Sleep(3);
}

///Function for game on easy mode
void EASY(int *v1,int *v2){
    srand(time(NULL));
    (*v1) = 1 + (rand() % 10);
    (*v2) = 1 + (rand() % 10);
}

///Function for game on medium mode
void MEDIUM(int *v1,int *v2){
    srand(time(NULL));
    (*v1) = 1 + (rand() % 100);
    (*v2) = 1 + (rand() % 100);
}

///Function for game on difficult mode
void DIFFICULT(int *v1,int *v2){
    srand(time(NULL));
    (*v1) = 1 + (rand() % 1000);
    (*v2) = 1 + (rand() % 1000);
}

///Function for game on extremely difficult mode
void E_DIFFICULT(int *v1,int *v2){
    srand(time(NULL));
    (*v1) = 1 + (rand() % 10000);
    (*v2) = 1 + (rand() % 10000);
}

///Function for ask user to CHOOSE a level for the game
void CHOOSE_LEVEL(int* level){
    printf("\n\nChoose the level:\n1 - | Easy\n2 - || Medium \n3 - ||| Difficult \n4 - |||| Extremely Difficult\n\n");
        scanf("%d",level);
}

void GOODLUCK(){
    system("cls");
    printf("\n\nGOOD LUCK ;)\n\n");
}


void MENU(void){
    MATHGAME player1;
    while(resp!=0){
        CHOOSE_LEVEL(&player1.level);
        GOODLUCK();
        Sleep(1);
        SHOW_SCORES();
        system("cls");


        switch (player1.level)
        {
        case 1:
            EASY(&player1.value1,&player1.value2);
            break;
        case 2:
            MEDIUM(&player1.value1,&player1.value2);
            break;
        case 3:
            DIFFICULT(&player1.value1,&player1.value2);
            break; 
        case 4:
            E_DIFFICULT(&player1.value1,&player1.value2);
            break;           
        
        default:
            printf("Invalid option!!!\n\n");
            break;
        }
        system("cls");
        CHOOSE_OPERATION(player1.value1,player1.value2);
        
        system("cls");
        CHECK_ANS(result);
        
        system("cls");
        ASK_NEWGAME(&resp);

    }
    system("cls");
    SHOW_SCORES();
    
    system("cls"); 
    printf("\n\nFinalizing the game...\n\n");
}


int main (){


    MENU();

    return 0;
}
