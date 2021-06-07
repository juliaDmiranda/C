#ifndef BANCO_H
#define BANCO_H

typedef struct banco *CONTAS;

void CriarConta(CONTAS conta);
int Sacar(CONTAS conta,int numeroDaConta, float *quantia);
int Depositar(CONTAS conta, int numeroDaConta, float quantia);
int Transferir(CONTAS conta,int numeroDaContaOrigem,int numeroDaContaDestino, float quantia);
void ListarContas(CONTAS conta);

CONTAS Inicializar();

void Destruir(CONTAS conta);

#endif