#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mercado.h"
/*Descrição:
Devemos desenvolver uma aplicação onde ao ser inicializada apresente ao usuário um menu onde seja
possível :
    -cadastrar
    -listar e comprar produtos
    - além de visualizar carrinho de compra ou sair da aplicação
Ao adicionar um produto no carrinho de compras, deve-se verificar se já existe um mesmo produto no
carrinho, bastando alterar a quantidade. 

Ao finalizar a compra deve ser apresentado ao usuário o total de acordo com os produtos e quantidades
inseridas no carrinho de compra.*/

//================================================================================================================================
// 
//                                              MERCARDO
//
//================================================================================================================================

//Estrutura para guardar informações dos produtos do mercado
typedef struct infos{
    char nome[60];            //Nome do produto    
    int codigo;            //Código do produto
    float preco;            //Preço do produto
    struct infos *prox; 
}INFO;

//Registro que contém informações do produto presente no mercado(contém lista)
struct Produtos
{
    INFO *lista;
};

//Função auxiliar de cadastro de novo produto. Cria novo elemento preenchendo com os parâmetros recebidos
//Retorna o novo elemento
INFO* NovoElemento(int codigo,char *nome,float preco){
    INFO *novo = (INFO*)malloc(sizeof(INFO));
    novo->codigo = codigo;
    strcpy(novo->nome,nome);
    novo->preco = preco;

    return novo;
}



//Funçao para buscar código de produto a ser cadastrado 
//Retorno: 0 se ele não existe e 1 caso exista
int BuscaCodigo(INFO *mercado,int codigo){

    if(mercado == NULL)//Se a lista que guarda todos os produtos do mercado estiver vazia, de certo o código não foi registrado
        return 0;
    else{
        INFO *aux = mercado;
        int  cod = -1;
        
        while(aux!=NULL && cod != codigo){
            cod = aux->codigo;
            aux = aux->prox;
        }

        if(cod == codigo) // PAra sair do loop ou chegamos ao fim da lista ou o código foi encontrado. Se o código não foi encontrado , então chegamos ao fim da lista.
            return 1;
        else 
          return 0;
    }
}

int BuscaProduto(PRODUTOS m, int codigo,char *nome,float *preco){
    if(m->lista == NULL){printf("\n\nLista VAZIA!\n\n");//Se a lista que guarda todos os produtos do mercado estiver vazia, de certo o código não foi registrado
        return 0;}
    else{
        INFO *aux = m->lista;
        int  cod = -1;
        
        while(aux!=NULL){
            cod = aux->codigo;
            if(cod == codigo){
              strcpy(nome, aux->nome);
              *preco = aux->preco;
              return 1;
            }
            aux = aux->prox;
        } 
        return 0;
    }
}

int CADASTRAR_PRODUTO(PRODUTOS mercado){
    int codigo;
    printf("------------------------------- CADASTRANDO UM NOVO PRODUTO -------------------------------------\n\n");
    printf("> CO'DIGO: ");
    scanf("%d",&codigo);
    if(!BuscaCodigo(mercado->lista,codigo)){//Se produto não for repetido
        char nome[60];
        float preco;

        //Continua o cadastramento
        printf("> NOME: ");
        fflush(stdin);
        scanf("%s",nome);
        printf("> PRECO: ");
        scanf("%f",&preco);

        INFO *novo = NovoElemento(codigo,nome,preco);

        if(mercado->lista == NULL){
          mercado->lista = novo;
          return 1;
        }

        INFO *aux = mercado->lista;
        while(aux->prox!=NULL)
            aux = aux->prox;
        
        aux->prox = novo; 

        return 1;

    }else{//Se o produto já foi registrado
        printf("Co'digo já registrado.");
        return 0;
    }
}

void MostrarMercado(PRODUTOS mercado){
    if(mercado->lista != NULL){
      INFO *aux = mercado->lista;

    printf("\n============= MERCADINHO PEDACINHO DO CE'U =============\n");
    while(aux!=NULL){
        printf("Co'digo: %d\nNome: %s\nPreco: %.2f",aux->codigo,aux->nome,aux->preco);
        printf("\n=======================================\n");
        aux = aux->prox;
    }}else
      printf("\nLista Vazia");
}

PRODUTOS Inicializar(){

    PRODUTOS mercado = (PRODUTOS)malloc(sizeof(struct Produtos));

    mercado->lista = NULL;

    return mercado;
}

PRODUTOS Destruir(PRODUTOS l){
    INFO *aux = l->lista;
    while(aux!=NULL){
        INFO *aux_prox = aux->prox;//aux_prox guarda o resto da lista após o anterior a ser removido
        
        free(aux);
        aux = aux_prox;
    }
    free(l);

    return NULL;
}
