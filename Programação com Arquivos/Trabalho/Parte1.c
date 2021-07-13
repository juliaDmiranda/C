#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
typedef struct Palavra
{
    char letras[50];    //caracteres que formam a palavra
    int qtdOcorrencias; //quantidade de vezes que essa palavra apareceu no arquivo
    int *linhas;        //vetor dinâmico
    struct Palavra *prox;
} t_palavra;

void MostrarLista(t_palavra *lista)
{
    t_palavra *aux = lista;

    while (aux != NULL)
    {
        printf("> Palavra: %s\n> Ocorrencias: %d\n> Linhas: ", aux->letras, aux->qtdOcorrencias);
        for (int i = 0; i < aux->qtdOcorrencias; i++)
        {
            if (i == aux->qtdOcorrencias - 1)
                printf("%d, ", aux->linhas[i]);
            else
                printf("%d, ", aux->linhas[i]);
        }
        printf("\n");
        aux = aux->prox;
    }
}

// Função para inicializar a lista
t_palavra *InicializaLista();

// Função para passar para letras minúsculas palavras que possuam letras maiúsculas
void TransformaLetraMaiusculaEmMinuscula(char* palavra);

// Função para inserir palavra em ordem alfabética na lista
t_palavra *InsereLista(t_palavra *lista, char *palavra, int linha);

// Função para verificar se determinada palavra já foi posta na lista
// Retorna: Ponteiro da palavra - palavra já existe, NULL - palavra não existe
// Retorna: 1 - palavra já existe, 0 - palavra não existe
t_palavra *Existe(t_palavra *lista, char *palavra);

//  Função para criar índice
void CriaIndice();

//  Função para busca de palavras através do índice já existente
void BuscaDePalavras();

//  Função de menu de opções do usuário
void Menu();

int main()
{
    //while(1)
    Menu();
    return 0;
}

t_palavra *InicializaLista()
{
    return NULL;
}

void TransformaLetraMaiusculaEmMinuscula(char *palavra){
    for(int i = 0; i < strlen(palavra); i++)
        if(isupper(palavra[i]))
            palavra[i] = tolower(palavra[i]);
}

t_palavra *Existe(t_palavra *lista, char *palavra)
{
    t_palavra *aux = lista;

    TransformaLetraMaiusculaEmMinuscula(palavra);
    while (aux != NULL)
    {
        if (!strcmp(aux->letras, palavra))
        {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

t_palavra *InsereLista(t_palavra *lista, char *palavra, int linha)
{
    t_palavra *nova_palavra = (t_palavra *)malloc(sizeof(t_palavra));

    nova_palavra->qtdOcorrencias = 1;

    strcpy(nova_palavra->letras, palavra);

    nova_palavra->linhas = (int *)malloc(1 * sizeof(int));

    nova_palavra->linhas[0] = linha;

    //Inserir ordenado alfabeticamente
    // OBS.: Ainda estou inserindo só no final
    t_palavra *aux = lista;
    nova_palavra->prox = lista;

    return nova_palavra;
}

void CriaIndice()
{
    char nomeDoArquivo[20] = "texto";
    char palavras[100];
    int qtdDePalavras = 0;
    int linha = 0;
    FILE *arq;

    // Perguntar o nome do arquivo texto
    // // printf("Insira o nome do arquivo: ");
    //fflush(stdin);
    //gets(nomeDoArquivo);

    //Abrir arquivo texto e ler cada palavra do arquivo
    arq = fopen(nomeDoArquivo, "r");

    if (arq != NULL)
    {
        t_palavra *lista = InicializaLista();
        char *palavra;

        while (fscanf(arq, " %[^\n]s ", palavras) != EOF) // Leitura de cada linha do arquivo
        {

            linha++; // marcação para linha


            palavra = strtok(palavras, " ");
            while (palavra != NULL)  // Análise de cada palavra do arquivo da linha atual
            { 

                t_palavra *aux_palavra = Existe(lista, palavra);

                //Checar se palavra já existe na lista
                if (!aux_palavra) // Se não
                {
                    qtdDePalavras++;
                    // Insere em ordem alfabética na lista
                    lista = InsereLista(lista, palavra, linha);
                }

                else // Se sim
                {
                    aux_palavra->qtdOcorrencias++;

                    // realloc no vetor linha
                    aux_palavra->linhas = (int *)realloc(aux_palavra->linhas, aux_palavra->qtdOcorrencias * sizeof(int));

                    // Adiciona o valor da  linha em que ela foi encontrada
                    aux_palavra->linhas[aux_palavra->qtdOcorrencias - 1] = linha;
                }
                palavra = strtok(NULL, " ");
            }
        }
        //Fechar arquivo
        fclose(arq);
        MostrarLista(lista);
                //MostrarLista(lista);
        /*
        POR EM OUTRA FUNÇÃO!(TALVEZ)
        // Criar e abrir arquivo binário "índice.dat"
        arq =  fopen("índice.dat", "a");

        fprintf(arq, "%d\n", qtdDePalavras);

        while(1){}
        /* i. Número inteiro contendo o total de palavras do índice
        ii. Cada palavra será representada por: um número inteiro contendo a quantidade
        de caracteres da palavra + 1, os caracteres da palavra em si junto com o ‘\0’, um
        número inteiro indicando a quantidade de vezes em que essa palavra foi
        encontrada no arquivo texto, e, finalmente as linhas onde a palavra foi
        encontrada (representada por um número inteiro).
        iii. Um esquema visual está apresentado abaixo. */

    }
}

void BuscaDePalavras();

void Menu()
{
    int opc=1;
    // printf ("\n1) criar um i'ndice para um arquivo texto;\n2) utilizar um i'ndice existente para realizar buscas por palavras;\n3) encerrar o programa.\n> ");
    //scanf("%d", &opc);

    switch (opc)
    {
    case 1: //  criar um índice para um arquivo texto
        CriaIndice();
        break;

    case 2: //  utilizar um índice existente para realizar buscas por palavras
        /* code */
        break;

    case 3: //  encerrar o programa
        exit(0);
        break;

    default:
        break;
    }
}

