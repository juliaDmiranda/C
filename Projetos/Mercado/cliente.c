#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cliente.h"

//================================================================================================================================
// 
//                                              CLIENTE
//
//================================================================================================================================

//Registro que contém informações do produto presente no mercado
typedef struct infos
{
    char nome[60];             //Nome do produto
    int codigo;             //Código do produto
    int quantidade;         //Quantidade comprada
    float preco;            //Preço do produto
    struct infos *prox;   //Ponteiro para o próximo produto
}INFO;

struct Produto{
  INFO *lista;
};


//Função que cria novo elemento para lista
//Esse novo elemento é preenchida pelas informações e é devolvido já preenchido
INFO* NovoElemento2(char *nome,int codigo,float preco){
  INFO *novo = (INFO*)malloc(sizeof(INFO));
  novo->prox = NULL;
  strcpy(novo->nome,nome);
  novo->codigo = codigo;
  novo->preco = preco;
  return novo;
}


//Função para verificar se determinado produto já foi adicionado ao carrinho de compras
int Existe(PRODUTO carrinho,int codigo,int quantidade){
  INFO *aux = carrinho->lista;
  while(aux != NULL){
    if(aux->codigo == codigo){
      aux->quantidade = aux->quantidade + quantidade;
      return 1;
    }
    aux = aux->prox;
  }

  return 0;
}

int ComprarProduto(PRODUTO carrinho,char *nome,int codigo,float preco,int quantidade){
  int existe;
  existe = Existe(carrinho, codigo, quantidade);
  if(!existe){
    INFO* novo;
    novo = NovoElemento2(nome,codigo,preco);
    novo->quantidade = quantidade;
    novo->prox = carrinho->lista;
    carrinho->lista = novo;
  }else if (existe == 1){
      return 1;
  }
  return 0;
}


//Função que calcula o total da comprar atual
float CalcularTotal(INFO *c){
  float total = 0;
  INFO *aux = c;

  while(aux!=NULL){
    total = total + (aux->preco * aux->quantidade);
    aux = aux->prox; 
  }
  return total;
}

void LISTAR_CARRINHO(PRODUTO carrinho){
  if(carrinho->lista != NULL){
    INFO *aux = carrinho->lista;
    printf("\n============= SEU CARRINHO =============\n");

    while(aux!=NULL){
      printf("Nome: %s\n Preco: %.2f\n Quantidade: %d",aux->nome,aux->preco,aux->quantidade);
      printf("\n=======================================\n");
      aux = aux->prox;
    }
    float total;
    total = CalcularTotal(carrinho->lista);
    printf("\nTOTAL A PAGAR : %.2f",total);

  }else
    printf("\nLista Vazia");  
}

PRODUTO InicializarCliente(){

    PRODUTO cliente= (PRODUTO)malloc(sizeof(struct Produto));

    cliente->lista = NULL;

    return cliente;
}


PRODUTO DestruirCliente(PRODUTO l){
    INFO *aux = l->lista;
    while(aux!=NULL){
        INFO *aux_prox = aux->prox;//aux_prox guarda o resto da lista após o anterior a ser removido
        
        free(aux);
        aux = aux_prox;
    }
    free(l);

    return NULL;
}


//Função para inicializar TAD que conterá todos os produtos do mercado

//POR ENQUANTO NÃO
/*
typedef struct Informacoes;
typedef struct Cliente;
//Registro para informações pessoais do usuário
typedef struct Informacoes
{
    char *nome; //nome do cliente
    int cpf;    //CPF do cliente

    int conta_mercadinho; //Cadastro no mercadinho do cliente para possível desconto

    float divida;

    //Registro do endereço do cliente, para possível entrega
    struct endereco
    {
        int cep;
        char *bairro;
        char *rua;
        char *cidade;
    } end;
} INFORMACOES;

//Registro geral do cliente: Carrinho
typedef struct Cliente
{
    float preco_total;
    INFORMACOES conta;
} CLIENTE;
*/

