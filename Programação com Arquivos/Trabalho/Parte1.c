#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Palavra
{
    char letras[50]; //caracteres que formam a palavra 
    int qtdOcorrencias; //quantidade de vezes que essa palavra apareceu no arquivo
    int *linhas; //vetor dinâmico
    struct Palavra* prox;
}t_palavra;

// Função para inicializar a lista
t_palavra* InicializaLista();

// Função para inserir palavra em ordem alfabética na lista
t_palavra* InsereLista(t_palavra* lista,char* palavra, int linha);

// Função para verificar se determinada palavra já foi posta na lista
// Retorna: Ponteiro da palavra - palavra já existe, NULL - palavra não existe
// Retorna: 1 - palavra já existe, 0 - palavra não existe
t_palavra* Existe(t_palavra* lista, char* palavra);

//  Função para criar índice
void CriaIndice();

//  Função para busca de palavras através do índice já existente
void BuscaDePalavras();

//  Função de menu de opções do usuário
void Menu();



int main(){
    while(1)
        Menu();
    return 0;
}

t_palavra* InicializaLista(){
    return NULL;
}

t_palavra* Existe(t_palavra* lista, char* palavra);

t_palavra* InsereLista(t_palavra* lista,char* palavra, int linha){
    t_palavra* nova_palavra = (t_palavra*)malloc(sizeof(t_palavra));
    
    nova_palavra->qtdOcorrencias = 1;
    
    strcpy(nova_palavra->letras, palavra);
    
    nova_palavra->linhas = (int*)malloc(sizeof(int));

    //Inserir ordenado alfabeticamente
    t_palavra* aux = lista;
    nova_palavra->prox = lista;

    return nova_palavra;
}

void CriaIndice(){
    int qntDePalavras = 0, linha = 1;
    char nomeDoArquivo[20], palavra[50];
    FILE* arq;

    // Perguntar o nome do arquivo texto
    printf("Insira o nome do arquivo: ");
    fflush(stdin);
    gets(nomeDoArquivo);

    //Abrir arquivo texto e ler cada palavra do arquivo
    arq = fopen(nomeDoArquivo, "r");

    if(arq != NULL)
    {    
        t_palavra* lista = InicializaLista();
        
        while(fread(palavra, sizeof(char), 1, arq))
        {
/*             if(!strcmp(palavra, "\n") || strcspn(palavra, "\n") == strlen(palavra) ) // Se for quebra 
                linha++; */
            //else{
                t_palavra* aux_palavra = Existe(lista, palavra);

                //Checar se palavra já existe na lista
                if (!aux_palavra)  // Se não
                {   
                    qntDePalavras++;
                    // Insere em ordem alfabética na lista
                        lista = InsereLista(lista, palavra, linha);
                }
                else  // Se sim
                {
                    aux_palavra->qtdOcorrencias++;
                        
                    // realloc no vetor linha
                    aux_palavra->linhas = (int*)realloc(aux_palavra->linhas, aux_palavra->qtdOcorrencias * sizeof(int));
                        
                    // Adiciona o valor da  linha em que ela foi encontrada
                    aux_palavra->linhas[aux_palavra->qtdOcorrencias];
                }
            //}
        }
    }
    //Fechar arquivo
    close(arq);
    

    // Criar e abrir arquivo binário "índice.dat"
    
    /* i. Número inteiro contendo o total de palavras do índice
    ii. Cada palavra será representada por: um número inteiro contendo a quantidade
    de caracteres da palavra + 1, os caracteres da palavra em si junto com o ‘\0’, um
    número inteiro indicando a quantidade de vezes em que essa palavra foi
    encontrada no arquivo texto, e, finalmente as linhas onde a palavra foi
    encontrada (representada por um número inteiro).
    iii. Um esquema visual está apresentado abaixo. */
    
    //Fecha arquivo
}

void BuscaDePalavras()
{
    // Liberar memória de lista

    // Abrir arquivo "índice.dat"
    
    /* b. Ler a quantidade de palavras (primeiro número inteiro do arquivo binário);
    c. Ler e mostrar na tela cada um dos registros subsequentes, contendo: um número inteiro
    que indica a quantidade de caracteres da palavra em questão (contando com o \0), os
    caracteres em si (incluindo o \0), um número inteiro que indica a quantidade de
    ocorrências dessa palavra no arquivo texto original e, finalmente, os números inteiros
    que representam as linhas onde a palavra foi encontrada. Esses dados também devem
    ser inseridos numa Lista de palavras.
    d. O programa deve então perguntar ao usuário qual palavra ele quer pesquisar;
    e. Se a palavra for encontrada, o programa deve mostrar na tela a quantidade de vezes em
    que ela existia no arquivo texto original e em quais linhas. Se não for encontrada, o
    programa deve avisar ao usuário.
    f. Após mostrar o resultado da busca, o programa deve voltar ao menu principal; */


}

void Menu()
{
    int opc;
    printf ("\n1) criar um i'ndice para um arquivo texto;\n2) utilizar um i'ndice existente para realizar buscas por palavras;\n3) encerrar o programa.");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:  //  criar um índice para um arquivo texto
        CriaIndice();
        break;

    case 2:  //  utilizar um índice existente para realizar buscas por palavras
        /* code */
        break;

    case 3:  //  encerrar o programa
        exit(0);
        break;
    
    default:
        break;
    }
}
