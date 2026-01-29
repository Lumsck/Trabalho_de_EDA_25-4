#include "Funções.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opcao;

void Menu_inicial() {
    printf("=== MENU INICIAL ===\n");
    printf("1. Gerenciamento de Clientes\n");
    printf("2. Gerenciamento de Produtos\n");
    printf("3. Carrinho de Compras\n");
    printf("0. Sair\n");

    scanf("%d", &opcao);
if (opcao == 1)
{
    Menu_clientes(opcao);
}
if (opcao == 2)
{
    Menu_produtos(opcao);
}
if (opcao == 3)
{
    Menu_compras(opcao);
}
if (opcao == 0)
{
    exit(0);
}

}


void Menu_clientes(int *ptr_opcao) {
    printf("=== GERENCIAMENTO DE CLIENTES ===\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Listar Clientes\n");
    printf("3. Editar Cliente\n");
    printf("4. Buscar Cliente pelo CPF\n");
    printf("5. Remover Cliente\n");
    printf("0. Voltar ao Menu Inicial\n");

    scanf("%d", ptr_opcao);

    if (*ptr_opcao == 1)
    {
        Cadastro_cliente();
    }
    if (*ptr_opcao == 2)
    {   //buguei de leve aqui
        imprime();
    }
    if (*ptr_opcao == 3)
    {
        /* code */
    }
    if (*ptr_opcao == 4)
    {
        //peguei inspirado do slide do professor
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

    }
    if (*ptr_opcao == 0)
    {
        Menu_inicial();
    }
    
}

void Cadastro_cliente() {

    int contador_clientes = 0;
        //to cozinhando esse daqui
    RegistroCliente *novo = malloc(sizeof(RegistroCliente));
    printf("Digite o CPF: ");
    scanf("%d", &novo->CPF);
    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf("%[^\n]", novo->nome);
    printf("Digite o email: ");
    novo->email = malloc(100 * sizeof(char));
    scanf("%s", novo->email);
    printf("Digite o telefone: ");
    scanf("%d", &novo->telefone);
    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf("%d", &novo->data_de_nascimento);
    novo->proximo = NULL;
    
}


void imprime (RegistroCliente *ponteiro) {
    // esse daqui tambem foi inspirado no slide do professor
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

void Menu_produtos(int *opcao) {
    printf("=== GERENCIAMENTO DE PRODUTOS ===\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Editar Produto\n");
    printf("4. Remover Produto\n");
    printf("0. Voltar ao Menu Inicial\n");
}

void Menu_compras(int *opcao) {
    printf("=== CARRINHO DE COMPRAS ===\n");
    printf("1. Realizar Compra\n");
    printf("2. Listar Compras\n");
    printf("0. Voltar ao Menu Inicial\n");
}

void Salva_dados() {
    // Implementação para salvar dados em arquivo, talvez?
}

void Carrega_dados() {
    // Implementação para carregar dados de arquivo?
}
