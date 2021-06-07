#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"banco.h"

typedef struct infos{
    char nomeCompleto[90];
    long int CPF,RG;
    char cidade[50],estado[3],bairro[50],rua[50];
}INFOS;

typedef struct cliente{
    INFOS informacoesPessoais;
    int numeroDaConta;
    float saldo;
    float dividas;
    int ultimoSaque;
    int ultimoDeposito;
    int ultimaTransferencia;
    struct cliente *prox;
}CLIENTE;

struct banco{
    CLIENTE *lista;
};

//Função auxiliar para criar novo elemento para a lista 
//O elemento já preenchido é retonrado
CLIENTE* NovoElemento(){

  CLIENTE *novoElemento = (CLIENTE*)malloc(sizeof(CLIENTE));
  
  printf("$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
  printf("\n|        DADOS PESSOAIS          |");         
  printf("\n|________________________________|\n"); 

  printf("\nNome do cliente___________");       
  scanf("%s",novoElemento->informacoesPessoais.nomeCompleto);
  
  printf("\nCPF___________");       
  scanf("%ld",&novoElemento->informacoesPessoais.CPF);

  printf("\nRG___________");       
  scanf("%ld",&novoElemento->informacoesPessoais.RG);
  
  printf("\nEstado___________");       
  scanf("%s",novoElemento->informacoesPessoais.estado);

  printf("\nCidade___________");       
  scanf("%s",novoElemento->informacoesPessoais.cidade);

  printf("\nBairro___________");       
  scanf("%s",novoElemento->informacoesPessoais.bairro);

  printf("\nRua___________");       
  scanf("%s",novoElemento->informacoesPessoais.rua);

  printf("$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");
  printf("\n|        DADOS DA CONTA          |");         
  printf("\n|________________________________|\n"); 

  printf("\nNu'mero da conta___________");       
  scanf("%d",&novoElemento->numeroDaConta);
  
  printf("\nSaldo___________");       
  scanf("%f",&novoElemento->saldo);

  printf("\nDividas___________");       
  scanf("%f",&novoElemento->dividas);

  novoElemento->prox = NULL;

  return novoElemento;

}

//Função auxiliar para inserir elemento em uma lista
//É inserido no início
CLIENTE* InserirNaLista(CLIENTE *lista){
  CLIENTE *inicio = NovoElemento();

  inicio->prox = lista;

  return inicio;
}

void CriarConta(CONTAS conta){
  conta->lista = InserirNaLista(conta->lista);
}

CLIENTE *BuscarConta(CLIENTE *lista,int numeroDaConta){
  CLIENTE *aux = lista;

  while(aux!=NULL){
    if(aux->numeroDaConta == numeroDaConta)
      return aux;
    aux = aux->prox;
  }

  return NULL;
}

int Sacar(CONTAS conta,int numeroDaConta, float *quantia){
  CLIENTE *minhaConta = BuscarConta(conta->lista,numeroDaConta);

  if(minhaConta == NULL){
    printf("\nConta inva'lida!\nNao foi possi'vel realizar o saque.\nPor favor, tente um valor va'lido.\n");
    return 0;
  }else{
    if(minhaConta->saldo < *quantia){
      printf("Voce so' tem %.2f disponi'vel.\nDeseja sacar todo o dinheito disponi'vel?\n(1) Sim\n(2) Nao\n> ",minhaConta->saldo);
      int resp;
      scanf("%d",&resp);

      if(resp == 1){
        *quantia = minhaConta->saldo;
        minhaConta->saldo = 0;
        return 1; 
      }else{
        printf("\nCancelando saque...\n");
        return 0;
      }
    }else{
      minhaConta->saldo = minhaConta->saldo - *quantia;
      printf("\nSaque efetuado com sucesso!\nResta-lhe R$%.2f de saldo.\n",minhaConta->saldo);
      return 1;
    }
  }
}

int Depositar(CONTAS conta, int numeroDaConta, float quantia){
  CLIENTE *minhaConta = BuscarConta(conta->lista,numeroDaConta);
  if(minhaConta == NULL){
    printf("\nConta inva'lida!\nNao foi possi'vel realizar o saque.\nPor favor, tente um valor va'lido.\n");
    return 0;
  }else{
    minhaConta->saldo = minhaConta->saldo + quantia;
    printf("\nDeposito realizado com sucesso!\nSaldo atualizado para R$%.2f",minhaConta->saldo);
    return 1;
  }
}

int Transferir(CONTAS conta,int numeroDaContaOrigem,int numeroDaContaDestino, float quantia){
  CLIENTE *destino,*origem;
  origem = BuscarConta(conta->lista,numeroDaContaOrigem);
  if(origem == NULL){
    printf("\nConta inva'lida!\nNao foi possi'vel realizar o saque.\nPor favor, tente um valor va'lido.\n");
    return 0;  
  }else if(origem->saldo <= quantia){
      printf("Voce so' tem %.2f disponi'vel.\nDeseja tranferir todo o dinheito disponi'vel?\n(1) Sim\n(2) Nao\n> ",origem->saldo);
      int resp;
      scanf("%d",&resp);
      if(resp == 1){
        destino = BuscarConta(conta->lista, numeroDaContaDestino);

        destino->saldo = destino->saldo + origem->saldo;

        origem->saldo = 0;

        printf("\nTranferencia realizada com sucesso!\n");

        return 1;
      }else{
        printf("\nCancelando saque...\n");
        return 0;
      }
  }else{
    destino = BuscarConta(conta->lista,numeroDaContaDestino);

    destino->saldo = destino->saldo + quantia;

    origem->saldo = origem->saldo - quantia;

    printf("\nTranferencia realizada com sucesso!\nSaldo atualizado para R$%.2f",origem->saldo);    

    return 1;
  }
}

//Função auxiliar para mostrar todas as contas depositadas na lista
void MostrarLista(CLIENTE *lista){
  CLIENTE *aux = lista;

  printf("$$$$$$$$$$$ BRAS BANC $$$$$$$$$$$$");       
  while(aux!=NULL){
    printf("\n________________________________\n"); 

    printf("\nNome do cliente___________%s",aux->informacoesPessoais.nomeCompleto);
    
    printf("\nCPF___________%ld",aux->informacoesPessoais.CPF);

    printf("\nRG___________%ld",aux->informacoesPessoais.RG);
    
    printf("\nEstado___________%s",aux->informacoesPessoais.estado);

    printf("\nCidade___________%s",aux->informacoesPessoais.cidade);

    printf("\nBairro___________%s",aux->informacoesPessoais.bairro);

    printf("\nRua___________%s",aux->informacoesPessoais.rua);

    printf("\nNu'mero da conta___________%d",aux->numeroDaConta);
    
    printf("\nSaldo___________%.2f",aux->saldo);

    printf("\nDividas___________%.2f",aux->dividas);   

    aux = aux->prox;
    printf("\n________________________________\n"); 
  }
}

void ListarContas(CONTAS conta){
  MostrarLista(conta->lista);
}


CONTAS Inicializar(){
    CONTAS conta = (CONTAS)malloc(sizeof(CONTAS));

    conta->lista = NULL;

    return conta;
}

void Destruir(CONTAS conta){
  CLIENTE *aux = conta->lista;
  CLIENTE *prox;

  while(aux!=NULL){
    prox = aux->prox;
    free(aux);
    aux = aux->prox;
  }

  free(conta);
}

