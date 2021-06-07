#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"banco.h"
// Devemos desenvolver uma aplicação onde ao ser inicializada solicite ao usuário escolher o que deseja
// fazer no banco, como criar uma conta, efetuar saque, efetuar depósito, efetuar transferência, listar contas
// ou sair

void MENU(CONTAS contas){
    int op, numeroDaConta,numeroDaContaDestino;
    float quantia;
    system("cls");
    printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
    printf("\n_________________________________\n");
    printf("|            MENU                |");
    printf("\n|________________________________|\n");
    printf("|                                |\n");
    printf("|(1) Criar conta                 |");
    printf("\n|(2) Efetuar saque               |");
    printf("\n|(3) Efetuar depo'sito           |");
    printf("\n|(4) Efetuar transferencia       |");
    printf("\n|(5) Listar contas               |");
    printf("\n|(6) Sair                        |");    
    printf("\n|________________________________|\n");
    printf("> ");
    scanf("%d",&op);

    switch (op)
    {
    case 1:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|           CRIAR CONTA          |");         
        printf("\n|________________________________|\n");       
        CriarConta(contas);
        break;
    case 2:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|             SAQUE              |");         
        printf("\n|________________________________|\n");  
        printf("\n> R$ ");
        scanf("%f", &quantia);
        printf("N° da Conta: ");
        scanf("%d", &numeroDaConta);
        Sacar(contas,numeroDaConta,&quantia);
        printf("\nVoce sacou R$%.2f", quantia);
        break;
    case 3:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|           DEPO'SITO            |");         
        printf("\n|________________________________|\n"); 
        printf("\n> R$ ");
        scanf("%f", &quantia);
        printf("N° da Conta: ");
        scanf("%d", &numeroDaConta);
        if(Depositar(contas,numeroDaConta,quantia))
          printf("\nVoce depositou R$%.2f", quantia); 
        break;
    case 4:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|           TRANFERENCIA         |");         
        printf("\n|________________________________|\n");  
        printf("\n> R$ ");
        scanf("%f", &quantia);
        printf("N° da Conta Origem: ");
        scanf("%d", &numeroDaConta);
        printf("N° da Conta Destino: ");
        scanf("%d", &numeroDaContaDestino);
        Transferir(contas,numeroDaConta,numeroDaContaDestino,quantia);
        break;
    case 5:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|             CONTAS             |");         
        printf("\n|________________________________|\n");  
        ListarContas(contas);
        break;
    case 6:
        system("cls");
        printf("\n\n$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
        printf("\n|     ENCERRANDO CONSULTA...     |");         
        printf("\n|________________________________|\n");  

        Destruir(contas);
        exit(0);
        break;    
    default:
        break;
    }
    system("pause");
}

int main(){
  CONTAS contas = Inicializar();

  while(1)
      MENU(contas);
  return 0;
}