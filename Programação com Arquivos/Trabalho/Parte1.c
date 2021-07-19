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
}Lista;

// Função para passar para letras minúsculas palavras que possuam letras maiúsculas
void TransformaLetraMaiusculaEmMinuscula(char* palavra);

// Função para inicializar a lista
Lista *InicializaLista();

// Função para liberar memória alocada para a lista
Lista* DesalocaLista(Lista* lista);

// Função para verificar se determinada palavra já foi posta na lista
// Retorna: Ponteiro da palavra - palavra já existe, NULL - palavra não existe
Lista *Existe(Lista *lista, char *palavra);

// Função para criar novo elemento que será inserido na lista em ordem alfabética
Lista* CriaElemento1(char* palavra, int linha);

// Função para inserir palavra em ordem alfabética na lista
Lista *InsereListaOrdenado(Lista *lista, char *palavra, int linha);

// Função para criar novo elemento que será inserido ao final da lista
Lista* CriaElemento2(t_palavra informacao);

// Função para inserir informações do índice em uma lista
Lista * InsereListaNoFinal(Lista*lista, t_palavra informacao);

// Função para criar índice em arquivo binário "índice.dat"
void CriaIndice(Lista* lista, int qtdPalavras);

//  Função para guardas as informações das palavras de um arquivo texto no registro Palavras, bem como a quantidade de palavras do arquivo
Lista* LeArqTextoParaLista(Lista* lista, int* qtdPalavras);

//  Função para mostrar informações sobre a palavra buscada pelo usuário
void MostraPalavra(t_palavra info);

//  Função para mostrar a leitura feita do arquivo "índice.dat"
void printLeArqBinParaLista(t_palavra informacao, int qtdCaracteres);

//  Função para ler as informações do índice do arquivo "índice.dat" armazenando um uma lista
Lista* LeArqBinParaLista(Lista* lista);

//  Função para busca de palavras através do índice já existente
void BuscaDePalavras(Lista* Lista);

//  Função de menu de opções do usuário
void Menu();

int main()
{
    Menu();
    return 0;
}

Lista *InicializaLista()
{
    return NULL;
}

Lista* DesalocaLista(Lista* lista){
    Lista* aux = lista;
    Lista* ant;

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

Lista *Existe(Lista *lista, char *palavra)
{
    Lista *aux = lista;

    TransformaLetraMaiusculaEmMinuscula(palavra); 

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

Lista* CriaElemento1(char* palavra, int linha){
    Lista *nova_palavra = (Lista *)malloc(sizeof(Lista));
    nova_palavra->info.qtdOcorrencias = 1;

    strcpy(nova_palavra->info.letras, palavra);

    nova_palavra->info.linhas = (int *)malloc(1 * sizeof(int));

    nova_palavra->info.linhas[0] = linha;

    nova_palavra->prox = NULL;

    return nova_palavra;
}


Lista *InsereLista(Lista *lista, char *palavra, int linha)
{
    Lista *aux, *ant;
    Lista *nova_palavra = CriaElemento1(palavra, linha);

    aux = lista;
    ant = NULL;

    if(lista != NULL){
        while(aux != NULL){
            if(strcmp(palavra, aux->info.letras) <= 0)
                break;
            ant = aux;
            aux = aux->prox;
        }
        if(ant == NULL){
            nova_palavra->prox = lista;
            lista = nova_palavra;
        }
        else{
            nova_palavra->prox = ant->prox;
            ant->prox = nova_palavra;
        }
        return lista;
    }

    return nova_palavra;
}


void CriaIndice(Lista* lista, int qtdPalavras){
    FILE* arq = fopen("índice.dat", "wb");  // Criar e abrir arquivo binário "índice.dat"

    Lista* aux = lista;

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

    fclose(arq);
}

Lista* LeArqTextoParaLista(Lista* lista, int* qtdPalavras){
    char nomeDoArquivo[20];
    char palavras[100];
    int linha = 0;
    FILE *arq;

    //Perguntar o nome do arquivo texto
    printf("Insira o nome do arquivo: ");
    fflush(stdin);
    gets(nomeDoArquivo);

    arq = fopen(nomeDoArquivo, "r");

    if (arq != NULL)
    {
        int tam;
        char *palavra;
        while (fscanf(arq, " %[^\n]s ", palavras) != EOF)
        {                                                      // Leitura de cada linha do arquivo
            linha++;                                                                                // marcação para linha

            palavra = strtok(palavras, " ");

            while (palavra != NULL)                                                                 // Análise de cada palavra do arquivo da linha atual
            {
                Lista *aux_palavra = Existe(lista, palavra);                                    //Checar se palavra já existe na lista

                if (!aux_palavra) // Se não
                {
                    *(qtdPalavras) = *(qtdPalavras) + 1;

                    lista = InsereLista(lista, palavra, linha);                                     // Insere em ordem alfabética na lista
                }

                else // Se sim
                {
                    aux_palavra->info.qtdOcorrencias++;

                    tam = aux_palavra->info.qtdOcorrencias;

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
    printf("> Quantidade de Ocorrencias: %d\n> Aparece na(s) linha(s):", info.qtdOcorrencias);

    for (int i = 0; i < info.qtdOcorrencias; i++)
        if(i == info.qtdOcorrencias - 1)
            printf(" %d", info.linhas[i]);
        else
            printf(" %d,", info.linhas[i]);

    printf("\n");
}

Lista* CriaElemento2(t_palavra informacao){
    Lista* novaPalavra = (Lista*)malloc(sizeof(Lista));

    strcpy(novaPalavra->info.letras, informacao.letras);

    novaPalavra->info.linhas = (int*)malloc(informacao.qtdOcorrencias * sizeof(int));

    for (int i = 0; i < informacao.qtdOcorrencias; i++)
        novaPalavra->info.linhas[i] = informacao.linhas[i];

    novaPalavra->info.qtdOcorrencias = informacao.qtdOcorrencias;

    novaPalavra->prox = NULL;

    return novaPalavra;
}

Lista* InsereListaNoFinal(Lista *lista, t_palavra informacao){
    Lista *novaPalavra  = CriaElemento2(informacao);
    Lista *aux = lista;
    Lista *ant = NULL;

    if(lista != NULL){

        while(aux != NULL)
        {
            ant = aux;
            aux = aux->prox;
        }

        ant->prox = novaPalavra;

        return lista;
    }else
        return novaPalavra;

}

void printLeArqBinParaLista(t_palavra informacao, int qtdCaracteres){
    printf("qtdCaracteres: %d\t", qtdCaracteres);
    printf("letras: %s\t", informacao.letras);
    printf("qtdOcorrencias: %d\t", informacao.qtdOcorrencias);
    printf("linhas: ");
    for (int i = 0; i < informacao.qtdOcorrencias; i++)
        if(i == informacao.qtdOcorrencias - 1)
            printf(" %d", informacao.linhas[i]);
        else
            printf(" %d,", informacao.linhas[i]);

    printf("\n\n");
}

Lista* LeArqBinParaLista(Lista* lista){
    FILE* arq = fopen("índice.dat", "rb");
    int qtdPalavras = 0 , qtdCaracteres;
    t_palavra informacao;

    // Inserir os valores em uma nova lista
    if(arq != NULL)
    {
        fread(&qtdPalavras, sizeof(int), 1, arq);

        printf("%d\n", qtdPalavras);

        for(int i=0; i < qtdPalavras; i++){
            fread(&qtdCaracteres, sizeof(int), 1, arq);                                     // Quantidade de caracteres

            fread(informacao.letras, sizeof(char), qtdCaracteres, arq);                     //  Palavra

            fread(&informacao.qtdOcorrencias, sizeof(int), 1, arq);                         //  Quantidade de ocorrências

            informacao.linhas = (int*)malloc((informacao.qtdOcorrencias) * sizeof(int));

            fread(informacao.linhas, sizeof(int), informacao.qtdOcorrencias, arq);          // Linhas de ocorrência

            printLeArqBinParaLista(informacao, qtdCaracteres);

            lista = InsereListaNoFinal(lista, informacao);
        }

        return lista;
    }
    return NULL;
}


void BuscaDePalavras(Lista* lista){
    Lista* informacoes;

    if(lista != NULL){
        char palavra[50];

        printf("> Palavra: ");          // Perguntar ao usuário a palavra
        // fflush(stdin);
        // gets(palavra);
        scanf("%s", palavra);
        informacoes = Existe(lista, palavra);  // Verificar se a palavra existe

        if(informacoes != NULL)
            MostraPalavra(informacoes->info);
        else
            printf("\nA palavra \"%s\" nao consta no documento.\n", palavra);
    }
}

void Menu(){
    Lista* lista = InicializaLista();

    int opc, qtdPalavras = 0;

    while(1)
    {
        system("cls");
        printf ("<1> criar um indice para um arquivo texto;\n<2> utilizar um indice existente para realizar buscas por palavras;\n<3> encerrar o programa.\n> ");
        scanf("%d", &opc);
        system("cls");
        switch (opc)
        {
            case 1: //  criar um índice para um arquivo texto
                lista = LeArqTextoParaLista(lista, &qtdPalavras);
                if(lista != NULL)
                    CriaIndice(lista, qtdPalavras);
                break;

            case 2: //  utilizar um índice existente para realizar buscas por palavras

                lista = LeArqBinParaLista(lista);

                system("pause");
                system("cls");

                BuscaDePalavras(lista);

                break;

            case 3: //  encerrar o programa
                exit(0);
                break;

            default:
                printf("Opcao inva'lida.");
                break;
            }

        if(lista != NULL)
            lista = DesalocaLista(lista);
        system("pause");
    }

}
