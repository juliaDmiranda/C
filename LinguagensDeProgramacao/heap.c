#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum algo_heap{First = 1, Best};

enum tipo_instrucao{set_heap = 1, new , del , exibe , atribui};

// Definir estrutura para cada variável criada
    //Campos:
        // nome da variável
        // tamanho da memória referenciada
        // posições da heap que esla está referenciando (vetor dinÂmico para alocar apartir do tamanho a ser alocado)
        // Ponteiro par ao proóximo

// Estrutura com informações de uma variável declarada no programa
typedef struct Variavel{
    char nome[20];          // nome da variável
    int qtdMem;             // tamanho da memória referenciada
    int bloco;             // Posiçaõ do bloco inicial livre / posições da heap que esla está referenciando (vetor dinÂmico para alocar apartir do tamanho a ser alocado)
}t_variavel;

// Estrutura do nó de uma lista de variáveis do programa
typedef struct ListaDeVariaveis{
    t_variavel info;                // Informações da variável
    struct ListaDeVariais *prox;    // Ponteiro para o próximo
}l_variavel;

void* InicializarLista(){
    return NULL;
}

// Definir lista que conterá o registro de áreas livres do heap
    //Campos
        // Endereço inicial da área livre
        // qtd fe blocos livres contíguos da área

// Estrutura de área livre do bloco
typedef struct AreaLivre{
    int inicio;                 // Posição do primeiro bloco livre no heap
    int qtdBlocosContiguos;     // Quantidade de blocos contíguos livres
}t_areaLivre;

// Estrutura de nó de lista contendo as áreas livres do heap
typedef struct ListaDeAreasLivres{
    t_areaLivre info;                   // Informações do nó
    struct ListaDeAreasLivres *prox;    // Ponteiro para o próximo
}l_areaLivre;

// Definir  estrutura de instrução
    // Campos:
        //strinf: tam 30+

// Estrutura para guardar partes da instrução // Inicializadas em '*'
typedef struct Instrucao{
    char str[20];
}t_instrucao;

/// Implementação do algoritmo first fit

// Função que executa o algoritmo first fit
l_areaLivre* FirstFit();

/// Implementação do Best fit

// Função que executa o algoritmo first fit
l_areaLivre* BestFit();

///Implementação do Worst fit
// Função que executa o algoritmo first fit
l_areaLivre* WorstFit();

// Função para realizar a atribuição
void Atribuir();

// Função de configuração do algoritmo para evitar segmentação externa do heap
void ConfigurarHeap();

// Função para realizar a instrução de declaração
void Declarar();

// Função para realizar a instrução de deletar
void Deletar();

// Função para exibir estado do heap
void Exibe();

// Função para executar programa
void ExecutarPrograma(char *nomeDoPrograma);

// Função para verificar o tipo de instrução
// Retorna um inteiro correspondente ao tipo
int VerificarInstrucao(t_instrucao *instrucao);

int main(){
    int heap[100] = {0}; // Estrutura do heap inicializada em 0's
    int marcadorHeap; //Marcador da implementação do momento
    char nomeDoArquivo[20] = "prog";
/*     printf("Nome do programa: ");
    fflush(stdin);
    gets(nomeDoArquivo); */
    ExecutarPrograma(nomeDoArquivo);
    return(0);
}



l_areaLivre* FirstFit(){

}


l_areaLivre* BestFit(){

}


l_areaLivre* WorstFit(){

}


void Atribuir(){
    // Atualiza lista de áreas livres pois, b não vai mais apontar para (se tiver coletor????)
    // Mudar campos de b para os campos de a
}


void ConfigurarHeap(){
    //atrualizar marcado da implementação do momento (talvez por essa enumeração com um enum)
}

void Declarar(){
    // Criar novo elemento para a lista de variáveis
    // Verificar marcado de implementação do heap do momento
    // Utilizar lista de áreas livres
    // Atualizar as áreas utilizadas para 1(???)
}

void Deletar(){
    // Procura na lista de variáveis a variável
    //Se não achar : variável não está lá
    //Se achar: Variável está lá
    //Verificar se outra variável está referenciando essa mesma área
    // Se não
    // Atualiza a lista de áreas livres
    // Atualiza heap nos campos que não estão sendo referenciados para 0

    // Se sim (vai servir também par ao se não - pelo menos para o final dele)
    // Desaloca o que foi aloca/ se foi alocado algum dos campos da variável
    // Retira nó de variável da lista
}

void Exibe(){
    // Mostrar estrutura da heap
    // Onde for 1 coloca * e onde for 0 não coloca nada
    // Imprime todas as variáveis
    // quantos blocos ela está referendo
    // quais índices do bloco
    // lista de áreas livres (talvez?)
}

int VerificarInstrucao(t_instrucao *instrucao){
    // Verificar se é atribuição:
    if(!strcmp(instrucao[1].str,"="))//Se for?
        return atribui;

    else// Se não for, verifica se é:
    {
        //declaração
        if(!strcmp(instrucao[0].str,"new"))
            return new;

        //configuração do heap
        else if(!strcmp(instrucao[0].str, "heap"))
            return set_heap;

        //deletar
        else if(!strcmp(instrucao[0].str, "del"))
            return del;

        //exibir heap
        else if(!strcmp(instrucao[0].str, "exibe"))
            return exibe;
    }
}

void ExecutarPrograma(char *nomeDoPrograma){
    FILE *arq = fopen(nomeDoPrograma, "r");

    // enquanto não está no final do arquivo de instruções
     if (arq != NULL)
    {
        l_variavel* listaVar = InicializarLista();
        l_areaLivre* listaAre = InicializarLista();

        char *palavra;
        char instrucao[30];
        
        int tipoDeInstrucao;
        int indice;
     
        t_instrucao vet_instrucao[3];  

        while (fscanf(arq, " %[^\n]s ", instrucao) != EOF)           // lê cada linha de instrução
        {     
            indice = 0;
            printf("\nInstrucao---> %s", instrucao);


            //(verificar de dá certo depois)for(palavra = strtok(instrucao, " "), indice = 0; palavra != NULL, indice < 3; palavra = strtok(NULL, " "), indice++);

            palavra = strtok(instrucao, " ");

            while (palavra != NULL)                                 // Análise de cada palavra da instrução
            {    
                strcpy(vet_instrucao[indice].str, palavra);         // Copiando para o vetor de cada palavra da instrução

                indice++;

                palavra = strtok(NULL, " ");
            }

            // Verificar o tipo de operação (<set_heap> | <new> | <del> | <exibe> | <atribui>)
            tipoDeInstrucao = VerificarInstrucao(vet_instrucao);

            switch (tipoDeInstrucao)
            {
                case set_heap:
                    ConfigurarHeap();
                    break;
                case new:
                    Declarar();
                    break;
                case del:
                    Deletar();
                    break;
                case exibe:
                    Exibe();
                    break;
                case atribui:
                    Atribuir();
                    break;
                default:
                    break;
            }

        }
        fclose(arq);

    }

    fclose(arq);
    while(!feof(arq)){

    }
}
