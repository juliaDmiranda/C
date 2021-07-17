#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Lemebrar de ler linha toda e usar strtok
// Talvez vá implementar lista de lixo (16/07/2021)
#define TAM_HEAP 40

enum algo_heap{First_Fit = 1, Best_Fit};

enum tipo_instrucao{set_heap = 1, new , del , exibe , atribui};

enum status_var{sofreuDel = -1};

enum status_heap{livre, alocado, lixo = -1 };

int MARCADOR_HEAP; //Marcador da implementação do momento
int linha = 0;

// Estrutura com informações de uma variável declarada no programa
typedef struct Variavel{
    char nome[20];          // nome da variável
    int qtdMem;             // tamanho da memória referenciada
    int blocoInicial;             // Posiçaõ do bloco inicial livre / posições da heap que esla está referenciando (vetor dinÂmico para alocar apartir do tamanho a ser alocado)
}t_variavel;

// Estrutura do nó de uma lista de variáveis do programa
typedef struct ListaDeVariaveis{
    t_variavel info;                // Informações da variável
    struct ListaDeVariais *prox;    // Ponteiro para o próximo
}l_variavel;

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

// Estrutura para guardar partes da instrução // Inicializadas em '*'
typedef struct Instrucao{
    char str[20];
}t_instrucao;

l_areaLivre* NovoElementoAreaLivre(int inicioDeAreaLivre, int qtdBlocosContiguos);

l_variavel* NovoElementoVariavel(char *nome, int blocoInicial, int qtdBlocosContiguos);
// Função para inicializar lista de área livre
l_areaLivre* InicializarListaAreaLivre();

// Função para inicializar lista de variáveis
l_variavel* InicializarListaVariavel();

void MostrarAreasLivres(l_areaLivre* lista);

void MostrarVariaveis(l_variavel *lista);

l_areaLivre* DestruirListaDeAreasLivres(l_areaLivre* lista);

l_areaLivre* DestruirListaDeVariaveis(l_variavel* lista);

void InserirListaDeVar(l_variavel **listaVar,int  n_inicioAlocado,int  qtdBlocosContiguos, char *nome);

// Função que executa o algoritmo First fit
void FirstFit(int *resp, l_areaLivre **listaAreaLivre, int *n_inicioAlocado, int mem);

// Função que executa o algoritmo Best fit
void BestFit(int *resp, l_areaLivre **listaAreaLivre, int *n_inicioAlocado, int mem);

///Implementação do Worst fit
// Função que executa o algoritmo Worst fit
l_areaLivre* WorstFit();

// Função para atualizar estado do vetor heap
void AtualizarHeap(int *heap, int indiceInicial, int indiceFinal, int status);

// Função para realizar a atribuição
void Atribuir();

// Função de configuração do algoritmo para evitar segmentação externa do heap
void ConfigurarHeap(t_instrucao *instrucao);

// Função para realizar a instrução de declaração
void Declarar(int* heap, l_variavel **listaVar, l_areaLivre **listaAreaLivre, t_instrucao* intrucao);

//  Função para atualizar lista de variáveis livres após deletar uma variável
void AtualizarListaDeAreasLivres(l_areaLivre **listaArea,int  n_blocoLivre, int n_blocosContiguosLivres);

//  Função para verificar se existem outras variáveis que apontam para a mesma área de memória que a variável deletada
void VerificarOutrasVariaveis(l_variavel** lista, int inicioBlocoLivre);


// Função para realizar a instrução de deletar
void Deletar(int *heap, l_variavel** listaVar, l_areaLivre** listaArea, char *variavel);

// Função para exibir estado do heap, (? lista de áreas livres e lista de variáveis)
void Exibe(l_variavel* listaVar, l_areaLivre* listaArea, int* heap);

// Função para executar programa
void ExecutarPrograma(char *nomeDoPrograma);

// Função para verificar o tipo de instrução
// Retorna um inteiro correspondente ao tipo
int VerificarInstrucao(t_instrucao *instrucao);

int main(){
    char nomeDoArquivo[20] = "prog";

/*   printf("Nome do programa: ");
    fflush(stdin);
    gets(nomeDoArquivo); */
    ExecutarPrograma(nomeDoArquivo);
    return(0);
}

void MostrarAreasLivres(l_areaLivre* lista){
    l_areaLivre* aux = lista;

    while(aux != NULL){
        printf("Inicio: %d   --  Blocos livres contiguos: %d\n", aux->info.inicio, aux->info.qtdBlocosContiguos);
        printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");

        aux = aux->prox;
    }
    system("pause");
    system("cls");
}

l_areaLivre* NovoElementoAreaLivre(int inicioDeAreaLivre, int qtdBlocosContiguos){
    l_areaLivre* novoElemento = (l_areaLivre*)malloc(sizeof(l_areaLivre));
    
    novoElemento->info.inicio = inicioDeAreaLivre;

    novoElemento->info.qtdBlocosContiguos = qtdBlocosContiguos;

    novoElemento->prox = NULL;

    return novoElemento;
}

l_areaLivre* InicializarListaAreaLivre(){
   l_areaLivre* areaLivreInicial = NovoElementoAreaLivre(0,100);

    return areaLivreInicial;
}

void MostrarVariaveis(l_variavel *lista){
    if(lista == NULL){
        printf("O programa ainda nao possui variaveis.\n");
    }    
    else{    
        l_variavel *aux = lista;

        while(aux != NULL){
            printf("%s -  Blocos alocados: %d   --  Inicio: %d\n", aux->info.nome, aux->info.qtdMem, aux->info.blocoInicial);
            printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");

            aux = aux->prox;
        }
    }
    system("pause");
    system("cls");
}

l_variavel* InicializarListaVariavel(){
    return NULL;
}

l_variavel* NovoElementoVariavel(char *nome, int blocoInicial, int qtdBlocosContiguos){
    l_variavel *novaVar = (l_variavel*) malloc(sizeof(l_variavel));

    strcpy(novaVar->info.nome, nome);

    novaVar->info.blocoInicial = blocoInicial; 
    novaVar->info.qtdMem = qtdBlocosContiguos;
    novaVar->prox = NULL;

    return novaVar; 
}

void InserirListaDeVar(l_variavel **listaVar,int  n_inicioAlocado,int  qtdBlocosContiguos, char *nome){
    l_variavel* aux = (*listaVar);
    l_variavel* ant = NULL;
    l_variavel* novaVar = NovoElementoVariavel(nome, n_inicioAlocado, qtdBlocosContiguos);

    while(aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
    }
    
    ant->prox = novaVar;
}

/* void FirstFit(int *resp, l_areaLivre **listaAreaLivre, int *n_inicioAlocado, int mem){
        // Utilizar lista de áreas livres

    //se deu para alocar
    (*resp) = 0;

} */

/* void BestFit(int *resp, l_areaLivre **listaAreaLivre, int *n_inicioAlocado, int mem){
        // Utilizar lista de áreas livres

    //se deu para alocar
    (*resp) = 0;

} */

void AtualizarHeap(int *heap, int indiceInicial, int indiceFinal, int status){
    for (int i = indiceInicial; i < indiceFinal; i++)
        heap[i] = status;
}

void Atribuir(){
/*     printf("\nAtribuir\n");
    system("pause");
    system("cls"); */
    // Atualiza lista de áreas livres pois, b não vai mais apontar para (se tiver coletor????)
    // Mudar campos de b para os campos de a
    
    // Verificar se b já referenciou alguma área
        // sim
            //atualiza lista de lixo
            // area do heap recebe -2 que sifnifica lixo
        // tranquilo
}

void ConfigurarHeap(t_instrucao *instrucao){
    printf("\nConfigurarHea analisando %s\n", instrucao[1].str);
    system("pause");
    system("cls");

    if(!strcmp(instrucao[1].str, "first"))
        MARCADOR_HEAP = First_Fit;

    else if(!strcmp(instrucao[1].str, "best"))
        MARCADOR_HEAP = Best_Fit;
}

void Declarar(int* heap, l_variavel **listaVar, l_areaLivre **listaAreaLivre, t_instrucao* instrucao){
/*     printf("\nDeclarar\n");
    system("pause");
    system("cls"); */
    int n_inicioAlocado;
    int resp = 0 ; // Resposta da operação
    int mem = atoi(instrucao[2].str);

    // Verificar marcado de implementação do heap do momento
    if(MARCADOR_HEAP == First_Fit)
        FirstFit(&resp, listaAreaLivre, &n_inicioAlocado, mem);
    else if(MARCADOR_HEAP == Best_Fit)
        BestFit(&resp, listaAreaLivre, &n_inicioAlocado, mem);
    if(!resp)
    {
        // Criar novo elemento para a lista de variáveis
        InserirListaDeVar(listaVar, n_inicioAlocado, mem, instrucao[1].str);
                
        // Atualizar heap, as áreas utilizadas para 1(???)
        AtualizarHeap(heap, n_inicioAlocado, mem, alocado);
    }                    

}

void MostrarOutrasVariaveis(char* nome, int inicioBlocoLivre){
    printf("- %s tambe'm referencia o bloco %d\n", nome, inicioBlocoLivre);
}


void VerificarOutrasVariaveis(l_variavel** lista, int inicioBlocoLivre){
    l_variavel* auxVar = (*lista);

    while (auxVar != NULL)
    {
        if (auxVar->info.blocoInicial == inicioBlocoLivre) // Se sim
        {
            //  Variável que for ela = var deletada recebe "-1"
            auxVar->info.blocoInicial = sofreuDel;
            MostrarOutrasVariaveis(auxVar->info.nome, inicioBlocoLivre);
        }
        auxVar = auxVar->prox;
    }
}

void Deletar(int *heap, l_variavel** listaVar, l_areaLivre** listaArea, char *variavel){
/*     printf("\nDeletar\n");
    system("pause");
    system("cls"); */
    
    int n_blocoLivre, n_blocosContiguosLivres; // guarda informação da área que for liberada (bloco inicial e áreas contiguas á ele)
    
    l_variavel *auxVar = (*listaVar);

    // Procura na lista de variáveis a variável
    while(auxVar != NULL)
    {
        if(!strcmp(auxVar->info.nome, variavel))
            break;
        
        auxVar = auxVar->prox;
    }    
    
    if(auxVar == NULL)      //Se não achar : variável não está lá 
        printf("Varia'vel inexistente\n");
    
    else{     //Se achar: Variável está lá
        
        // copiar informações da variável que vai ser deletada
        n_blocoLivre = auxVar->info.blocoInicial;
        n_blocosContiguosLivres = auxVar->info.qtdMem;

        // Atualizar status de variávels 
        auxVar->info.blocoInicial = sofreuDel;                              

        //Verificar se outra variável está referenciando essa mesma área
        VerificarOutrasVariaveis(listaVar, n_blocoLivre);

        // Atualiza a lista de áreas livres
        AtualizarListaDeAreasLivres(listaArea, n_blocoLivre, n_blocosContiguosLivres);

        // Atualiza heap nos campos que não estão sendo referenciados para 0
        AtualizarHeap(heap, n_blocoLivre, n_blocosContiguosLivres, livre);
        
    }
   
}

void MostrarHeap(int* heap){
    for (int i = 0; i < TAM_HEAP; i++)
    {
        if(heap[i] == livre){
            if( i == 0 )
                printf("|   |");
            else
                printf("   |");
        }else if(heap[i] == alocado){
            if( i == 0 )
                printf("| * |");
            else
                printf(" * |");
        }else if(heap[i] == lixo){
            if( i == 0 )
                printf("|lixo|");
            else
                printf("lixo|");
        }
    }
    printf("\n");
    system("pause");
    system("cls");
}

void Exibe(l_variavel* listaVar, l_areaLivre* listaArea, int* heap){
    printf("\nExibe\n");
    system("pause");
    system("cls");
    // Mostrar estrutura da heap
    // Onde for 1 coloca * e onde for 0 não coloca nada
    // Imprime todas as variáveis
        // quantos blocos ela está referendo
        // quais índices do bloco
    MostrarHeap(heap);
    MostrarVariaveis(listaVar);
    MostrarAreasLivres(listaArea);
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
        else
            return -1; // erro
    }
}

void ExecutarPrograma(char *nomeDoPrograma){
    FILE *arq = fopen(nomeDoPrograma, "r");
    int heap[TAM_HEAP] = {livre}; // Estrutura do heap inicializada em 0's

    // enquanto não está no final do arquivo de instruções
     if (arq != NULL)
    {
        l_variavel* listaVar = InicializarListaVariavel();
        l_areaLivre* listaAre = InicializarListaAreaLivre();

        char *palavra;
        char instrucao[30];
        
        int tipoDeInstrucao;
        int indice;

        t_instrucao vet_instrucao[3];  

        while (fscanf(arq, " %[^\n]s ", instrucao) != EOF)           // lê cada linha de instrução
        {     
            linha++;
            indice = 0;

            printf("\n%d| %s",linha, instrucao);

            for(palavra = strtok(instrucao, " "); palavra != NULL; palavra = strtok(NULL, " "))
            {
                strcpy(vet_instrucao[indice].str, palavra);         // Copiando para o vetor de cada palavra da instrução
                indice++;
            }

            // Verificar o tipo de operação (<set_heap> | <new> | <del> | <exibe> | <atribui>)
            tipoDeInstrucao = VerificarInstrucao(vet_instrucao);

            switch (tipoDeInstrucao)
            {
                case set_heap:
                    ConfigurarHeap(vet_instrucao);

                    break;
                case new:
                    Declarar(heap, &listaVar, &listaAre, vet_instrucao);

                    break;
                case del:
                    Deletar(heap, &listaVar, &listaAre, vet_instrucao[1].str);

                    break;
                case exibe:
                   Exibe(listaVar, listaAre, heap);
                    break;
                case atribui:
                    //Atribuir();
                    break;
                default:
                    break;
            }

        }
        fclose(arq);

    }

}
