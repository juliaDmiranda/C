#include<stdio.h>
#include<stdlib.h>

typedef struct Lista{
    int num;
    float num1;
    struct Lista *prox;
}t_lista;

void insere(t_lista** listaRef, int num, float num2){
    t_lista* novo_elemento = (t_lista*)malloc(sizeof(t_lista));
    novo_elemento->num = num;
    novo_elemento->num1 = num2;

    novo_elemento->prox = (*listaRef);
    (*listaRef) = novo_elemento;
}

void mostra(t_lista* lista){
    t_lista *aux = lista;

    while(aux!=NULL){
        printf("num: %d e num1: %.2f\n", aux->num,aux->num1);
        aux = aux->prox;
    }
    system("pause");
    system("cls");
}

void deleta(t_lista** lista,int num){
    t_lista *aux = (*lista);
    t_lista *ant = NULL;

    while(aux!=NULL){
        if(aux->num == num)
            break;
        ant = aux;
        aux = aux->prox;
    }
    if(aux!=NULL){    /* retira elemento */
        if (ant == NULL) {
        /* retira elemento do inicio */
            (*lista) = aux->prox;
        }

        else {
            /* retira elemento do meio da lista */
            ant->prox = aux->prox;
        }
        free(aux);
    }
}


int main(){
    int opc,var1,var2;
    t_lista *lista = NULL;

    while(1){
        printf("<1>insere\n<2>mostra\n<3>deleta\n<4>sai\n>");
        scanf("%d", &opc);

        if(opc == 1){
            printf("var1: ");
            scanf("%d", &var1);
            printf("var2: ");
            scanf("%d", &var2);
            system("cls");
            insere(&lista, var1,var2);
        }else if(opc == 2){
            mostra(lista);
        }else if(opc== 3){
            printf("num: ");
            scanf("%d", &var1);

            deleta(&lista, var1);
        }else if(opc== 4){
            exit(0);
        }
    }
}
