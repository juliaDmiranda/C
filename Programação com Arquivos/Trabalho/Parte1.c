#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct Palavra
{
    char letras[50];    //caracteres que formam a palavra
    int qtdOcorrencias; //quantidade dez vezes que essa palavra apareceu no arquivo
    int *linhas;        //vetor dinâmico
} t_palavra;

typedef struct Lista{
    t_palavra info;
    struct Lista *prox;
}t_lista;

void MostrarLista(t_lista *lista)
{
    t_lista *aux = lista;

    while (aux != NULL)
    {
        printf("> Palavra: %s\n> Ocorrencias: %d\n> Linhas: ", aux->info.letras, aux->info.qtdOcorrencias);
        for (int i = 0; i < aux->info.qtdOcorrencias; i++)
        {
            if (i == aux->info.qtdOcorrencias - 1)
                printf("%d, ", aux->info.linhas[i]);
            else
                printf("%d, ", aux->info.linhas[i]);
        }
        printf("\n");
        aux = aux->prox;
    }
}

// Função para liberar memória alocada para a lista
t_lista* DesalocaLista(t_lista* lista);

// Função para inicializar a lista
t_lista *InicializaLista();

// Função para passar para letras minúsculas palavras que possuam letras maiúsculas
void TransformaLetraMaiusculaEmMinuscula(char* palavra);

// Função para inserir palavra em ordem alfabética na lista
t_lista *InsereLista(t_lista *lista, char *palavra, int linha);

// Função para inserir informações do índice em uma lista
t_lista * InsereListaNoFinal(t_lista*lista, t_palavra informacao);

// Função para verificar se determinada palavra já foi posta na lista
// Retorna: Ponteiro da palavra - palavra já existe, NULL - palavra não existe
t_lista *Existe(t_lista *lista, char *palavra);

// Função para criar índice em arquivo binário "índice.h"
void CriaIndice(t_lista* lista, int qtdPalavras);

//  Função para guardas as informações das palavras de um arquivo texto no registro Palavras, bem como a quantidade de palavras do arquivo
t_lista* LeArqTextoParaLista(t_lista* lista, int* qtdPalavras);

//  Função para mostrar informações sobre a palavra buscada pelo usuário
void MostraPalavra(t_palavra info);

//  Função para busca de palavras através do índice já existente
void BuscaDePalavras(t_lista* Lista);

//  Função para ler as informações do índice do arquivo "índice.dat" armazenando um uma lista
t_lista* LeArqBinParaLista(t_lista* lista);

//  Função de menu de opções do usuário
void Menu();

int main()
{
    Menu();
    return 0;
}

t_lista *InicializaLista()
{
    return NULL;
}

t_lista* DesalocaLista(t_lista* lista){
    t_lista* aux = lista;
    t_lista* ant;

    while(aux != NULL){
        ant = aux;

        aux = aux->prox;

        free(ant->info.linhas);

        free(ant);
    }

    return NULL;
}

void TransformaLetraMaiusculaEmMinuscula(char *palavra){
    int tam = strlen(palavra);
    for(int i = 0; i < tam; i++)
        if(isupper(palavra[i]))
            palavra[i] = tolower(palavra[i]);
}

t_lista *Existe(t_lista *lista, char *palavra)
{
    t_lista *aux = lista;

    TransformaLetraMaiusculaEmMinuscula(palavra); // Dar um jeito 1- verifica 2- n verifica (quando for só busca) mexer depois

    while (aux != NULL)
    {
        if (!strcmp(aux->info.letras, palavra))
        {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

//Falta inserir em ordem alfabética
t_lista *InsereLista(t_lista *lista, char *palavra, int linha)
{
    t_lista *nova_palavra = (t_lista *)malloc(sizeof(t_lista));

    nova_palavra->info.qtdOcorrencias = 1;

    strcpy(nova_palavra->info.letras, palavra);

    nova_palavra->info.linhas = (int *)malloc(1 * sizeof(int));

    nova_palavra->info.linhas[0] = linha;

    t_lista *aux = lista;
    nova_palavra->prox = lista;

    return nova_palavra;
}

t_lista * InsereListaNoFinal(t_lista* lista, t_palavra informacao){

    t_lista* novaPalavra = (t_lista*)malloc(sizeof(t_lista));

    strcpy(novaPalavra->info.letras, informacao.letras);

    novaPalavra->info.linhas = (int*)malloc(informacao.qtdOcorrencias * sizeof(int));

    for (int i = 0; i < informacao.qtdOcorrencias; i++)
        novaPalavra->info.linhas[i] = informacao.linhas[i];

    novaPalavra->info.qtdOcorrencias = informacao.qtdOcorrencias;

    novaPalavra->prox = NULL;

    if(lista != NULL){
        t_lista* aux = lista;
        t_lista* ant;

        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
        }

        ant->prox = novaPalavra;
        return lista;
    }

    return novaPalavra;
}

void CriaIndice(t_lista* lista, int qtdPalavras){
    FILE* arq = fopen("índice.dat", "w+b");                                     // Criar e abrir arquivo binário "índice.dat"
    
    t_lista* aux = lista;
    
    int tamDaPalavra, qtdOcorrencias;

    fwrite(&qtdPalavras, sizeof(int), 1, arq); // Número inteiro contendo o total de palavras do índice
    
    while (aux != NULL)
    {
        tamDaPalavra = strlen(aux->info.letras) + 1;
        qtdOcorrencias = aux->info.qtdOcorrencias;

        fwrite(&tamDaPalavra, sizeof(int), 1, arq); // um número inteiro contendo a quantidade de caracteres da palavra + 1

        fwrite(aux->info.letras, sizeof(char), tamDaPalavra, arq); // os caracteres da palavra em si junto com o ‘\0’

        fwrite(&aux->info.qtdOcorrencias, sizeof(int), 1, arq); // número inteiro indicando a quantidade de vezes em que essa palavra foi encontrada no arquivo texto

        fwrite(aux->info.linhas, sizeof(int), aux->info.qtdOcorrencias, arq); // as linhas onde a palavra foi encontrada (representada por um número inteiro)

        aux = aux->prox;
    }
}

t_lista* LeArqTextoParaLista(t_lista* lista, int* qtdPalavras){
    char nomeDoArquivo[20] = "texto";
    char palavras[200];
    int linha = 0;
    FILE *arq;

    // Perguntar o nome do arquivo texto
    // printf("Insira o nome do arquivo: ");
    //fflush(stdin);
    //gets(nomeDoArquivo);

    arq = fopen(nomeDoArquivo, "r");

    if (arq != NULL)
    {
        char *palavra;
        while (!feof(arq))                       
        {
            fscanf(arq, " %[^\n]s ", palavras);                                                      // Leitura de cada linha do arquivo
            
            linha++;                                                                                // marcação para linha
            
            palavra = strtok(palavras, " ");
            
            while (palavra != NULL)                                                                 // Análise de cada palavra do arquivo da linha atual
            {
                t_lista *aux_palavra = Existe(lista, palavra);                                    //Checar se palavra já existe na lista
                
                if (!aux_palavra) // Se não
                {
                    *(qtdPalavras) = *(qtdPalavras) + 1;
                    lista = InsereLista(lista, palavra, linha);                                     // Insere em ordem alfabética na lista
                }
                
                else // Se sim
                {
                    int tam  = aux_palavra->info.qtdOcorrencias++;

                    aux_palavra->info.linhas = (int *)realloc(aux_palavra->info.linhas, tam * sizeof(int));   // realloc no vetor linha
                    
                    aux_palavra->info.linhas[tam - 1] = linha;                                                // Adiciona o valor da  linha em que ela foi encontrada
                }
                
                palavra = strtok(NULL, " ");
            }
        }
        fclose(arq);

    }

    fclose(arq);

    return lista;
}

void MostraPalavra(t_palavra info){
    info.letras[0] = toupper(info.letras[0]);
    printf("\nQuantidade de Ocorrencias: %d\nAparicoes(por linha):", info.qtdOcorrencias);

    for (int i = 0; i < info.qtdOcorrencias; i++)
        printf("\t%d", info.linhas[i]);

    printf("\n");
    system("pause");

    system("cls");
}

t_lista* LeArqBinParaLista(t_lista* lista){
    FILE* arq = fopen("índice.dat", "rb");

    // Inserir os valores em uma nova lista
    if(arq != NULL)
    {
        int qtdPalavras, qtdCaracteres;
        t_palavra informacao;

        fread(&qtdPalavras, sizeof(int), 1, arq);
        printf("%d\n", qtdPalavras);

        while(feof(arq) == 0){
            fread(&qtdCaracteres, sizeof(int), 1, arq);                                     // Quantidade de caracteres
            printf("%d\t", qtdCaracteres);

            fread(informacao.letras, sizeof(char), qtdCaracteres, arq);                     //  Palavra
            printf("%s\t", informacao.letras);

            fread(&informacao.qtdOcorrencias, sizeof(int), 1, arq);                         //  Quantidade de ocorrências
            printf("%d\t", informacao.qtdOcorrencias);

            informacao.linhas = (int*)malloc((informacao.qtdOcorrencias) * sizeof(int));

            fread(informacao.linhas, sizeof(int), informacao.qtdOcorrencias, arq);          // Linhas de ocorrência

            for (int i = 0; i < informacao.qtdOcorrencias; i++)
                printf("%d\t", informacao.linhas[i]);

            printf("\n\n");

            lista = InsereListaNoFinal(lista, informacao);
        }
    }
    return lista;
}

void BuscaDePalavras(t_lista* lista){
    t_lista* info;

    if(lista != NULL){
        char palavra[50];

        printf("> Palavra: ");          // Perguntar ao usuário a palavra
        fflush(stdin);
        gets(palavra);

        info = Existe(lista, palavra);  // Verificar se a palavra existe

        if(info != NULL)
        {
            MostraPalavra(info->info);
        }

        else
            printf("\nA palavra \"%s\" nao conta no documento.\n", palavra);
    }
}

void Menu(){
    t_lista* lista = InicializaLista();
    int opc, qtdPalavras = 0;

    while(1)
    {
        printf ("<1> criar um indice para um arquivo texto;\n<2> utilizar um indice existente para realizar buscas por palavras;\n<3> encerrar o programa.\n> ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch (opc)
        {
            case 1: //  criar um índice para um arquivo texto
                lista = LeArqTextoParaLista(lista, &qtdPalavras);

                CriaIndice(lista, qtdPalavras);
                break;

            case 2: //  utilizar um índice existente para realizar buscas por palavras

                lista = LeArqBinParaLista(lista);

                system("pause");
                system("cls");

                BuscaDePalavras(lista);

                remove("índice.dat");
                break;

            case 3: //  encerrar o programa
                exit(0);
                break;

            default:
                printf("Opcao inva'lida.");
                break;
            }
    }

    if(lista != NULL)
        lista = DesalocaLista(lista);

}
