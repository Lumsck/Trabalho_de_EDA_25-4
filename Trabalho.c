//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//////////////////////////// REQUISITOS TÉCNICOS ///////////////////////////////////////
/*
    Implementação exclusivamente em C;
    Repositório git com contribuição de todos os membros do grupo e espaçados ao longo do tempo;
    Uso obrigatório de listas simplesmente encadeadas;
    Uso de alocação dinâmica de memória (malloc, calloc, realloc e free);
    Proibido o uso de variáveis globais;
    Manipulação das listas por passagem de parâmetros;
    Menu funcional via terminal;
*/

//////////////////////////// FUNCIONALIDADES ///////////////////////////////////////
/* 

//Gerenciamento de clientes
//Gerenciamento de produtos
//Modo compra

*/ 

//////////////////////////// ÁREA CLIENTES ///////////////////////////////////////


//Cadastro e lista de clientes

typedef struct Cadastro {
    int CPF;
    char nome[];
    char email[];
    int telefone;
    int data_de_nascimento;
    struct Cadastro * proximo;
} RegistroCliente;

//Listar clientes

void imprime (RegistroCliente *ponteiro) {
    RegistroCliente *atual = ponteiro;
    while (atual != NULL) {
        printf("CPF: %d\n", atual->CPF);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Telefone: %d\n", atual->telefone);
        printf("Data de Nascimento: %d\n", atual->data_de_nascimento);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

//Buscar cliente pelo CPF

RegistroCliente * buscaCPF(RegistroCliente *ponteiro, int CPF) {
    RegistroCliente *atual = ponteiro;
    while (atual != NULL) {
        if (atual->CPF == CPF) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

//Editar dados de um cliente



//Remover cliente

//////////////////////////// PRODUTOS ///////////////////////////////////////
/*

//Cadastrar produto

//Listar todos os produtos

//Buscar produto pelo código

//Editar dados de um produto

//Remover produto

*/

//////////////////////////// MODO COMPRA ///////////////////////////////////////
/*

//Incluir produtos no carrinho

//Listar produtos e informar valor total e qtd de itens

//Retirar produtos do carrinho do cliente

*/
