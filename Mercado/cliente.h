#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct Produto *PRODUTO;


//Função para comprar um novo produto desde que ele esteja disponível no mercadinho
int ComprarProduto(PRODUTO carrinho,char *nome,int codigo,float preco,int quantidade);

//Função que mostra carrinho de compra de cliente atual e o total a ser pago até o momento
void LISTAR_CARRINHO(PRODUTO carrinho);

//Função que finaliza compra mostrando o total a ser pago bem como todos os produtos comprados
float Finalizar_Compra(PRODUTO carrinho);

//Função que inicializa TAD
PRODUTO InicializarCliente();

//Função que destroi TAD
PRODUTO DestruirCliente(PRODUTO l);
#endif