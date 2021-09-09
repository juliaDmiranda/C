#ifndef MERCADO_H
#define MERCADO_H

typedef struct Produtos *PRODUTOS;//Estrutura para produtos do mercado

//Funçao para buscar código de produto a ser cadastrado 
//Retorno: 0 se ele não existe e 1 caso exista
//Retorna por referência as informações do produto
int BuscaProduto(PRODUTOS m, int codigo,char *nome,float *preco);

//Função que cadastra o produto e retorna o carrinho de compras atualizado
int CADASTRAR_PRODUTO(PRODUTOS mercado);

//Função que lista todos os produtos disponíveis para compra incluindo suas insformações adicionais
void MostrarMercado(PRODUTOS mercado);

//Função para iniciar TAD
PRODUTOS Inicializar();

//Função para destruir TAD
PRODUTOS Destruir(PRODUTOS l);

#endif

