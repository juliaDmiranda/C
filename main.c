#include<stdio.h>
#include<stdlib.h>
#include"mercado.h"
#include "cliente.h"

float total;//Preço total a ser pago na compra

enum opcoes{cadastrar = 1,listar_produtos,adicionar_produto,ver_carrinho,finalizar}; // Utilizado para ficar mais clara as opções no switch case da função MENU()


//Cabeçalho da função MENU()
void MENU(PRODUTOS mercado,PRODUTO carrinho);

int main(){
    PRODUTO meu_carrinho; // TAD do carrinho de comprar do cliente
    PRODUTOS M_PedacoDoCeu; // TAD do Mercado Pedaço do Céu

    M_PedacoDoCeu = Inicializar();
    meu_carrinho = InicializarCliente();

    while (1)
    {
        MENU(M_PedacoDoCeu,meu_carrinho);
        system("pause");
        system("cls");
    }
    return 0;
}

void MENU(PRODUTOS mercado,PRODUTO carrinho)
{
    int op;
    printf("\n\n------------- BEM - VINDO(A) AO SUPERMERCADO PEDACO DO CE'U -----------");
    printf("\n(1) > Cadastrar");
    printf("\n(2) > Lista de produtos");
    printf("\n(3) > Adicionar produto ao carrinho");
    printf("\n(4) > Vizualizar carrinho de compra");
    printf("\n(5) > Finalizar compra");
    printf("\n>> ");
    scanf("%d", &op);
    system("cls");
    
    char nome[60];
    int codigo;
    float preco;
    int quantidade;
    int existe;

    switch (op)
    {
    case cadastrar:
        CADASTRAR_PRODUTO(mercado);
        break;
    case listar_produtos:
        MostrarMercado(mercado);
        break;
    case adicionar_produto:
        printf("Insira o co'digo: ");

        scanf("%d",&codigo);

        if(!BuscaProduto(mercado, codigo, nome, &preco))
          printf("\nEsse produto não existe no mercado :(\n");
        else{
          printf("Insira a quantidade de %s: ",nome);

          scanf("%d",&quantidade);

          ComprarProduto(carrinho,nome,codigo,preco, quantidade);
        }
        break;
    case ver_carrinho:
        LISTAR_CARRINHO(carrinho);
        break;

    case finalizar:
        printf("Compra finalizada com sucesso!\nVeja seus produtos abaixo...\n\n\n");
        LISTAR_CARRINHO(carrinho);
        Destruir(mercado);
        DestruirCliente(carrinho);
        printf("\n\nO mercado Pedacinho do Ce'u agradece a compra! :)\n\n");
        exit(0);
        break;

    default:
        printf("\nPrezado cliente.\nPor favor, insira uma opcao va'lida\n");
        break;
    }

}