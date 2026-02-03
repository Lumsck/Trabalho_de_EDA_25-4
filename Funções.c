#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"

void Menu_inicial() {
    int opcao;
    RegistroCliente *lista_clientes = NULL; 

    do {
        printf("\n=== MENU INICIAL ===\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("2. Gerenciamento de Produtos\n");
        printf("3. Carrinho de Compras\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                Menu_clientes(&lista_clientes);
                break;
            case 2:
                Menu_produtos();
                break;
            case 3:
                Menu_compras();
                break;
            case 0:

                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    free(lista_clientes);
}

void Menu_clientes(RegistroCliente **ptr_lista_clientes) {
    int opcao;

    do {
        printf("\n=== GERENCIAMENTO DE CLIENTES ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Buscar Cliente pelo CPF\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar ao Menu Inicial\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                Cadastro_cliente(ptr_lista_clientes);
                break;
            case 2:
                Imprime_clientes(*ptr_lista_clientes); 
                break;
            case 3:
                printf("Funcao Editar em desenvolvimento...\n");
                break;
            case 4:
                long long cpf_busca;
                printf("Digite o CPF: ");
                scanf("%lld", &cpf_busca);
                RegistroCliente *res = buscaCPF(*ptr_lista_clientes, cpf_busca);
                if(res) printf("Encontrado: %s\n", res->nome);
                else printf("Nao encontrado.\n");
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void Cadastro_cliente(RegistroCliente **ptr_lista_clientes) {
    RegistroCliente *novo = (RegistroCliente*) malloc(sizeof(RegistroCliente));
    
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("Digite o CPF: ");
    scanf("%lld", &novo->CPF);
    
    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf(" %[^\n]", novo->nome); 
    
    printf("Digite o email: ");
    novo->email = malloc(100 * sizeof(char));
    scanf(" %s", novo->email);
    
    printf("Digite o telefone: ");
    scanf("%lld", &novo->telefone);
    
    printf("Digite a data de nascimento (DDMMAAAA): ");
    scanf("%d", &novo->data_de_nascimento);

    novo->proximo = *ptr_lista_clientes;
    *ptr_lista_clientes = novo;
    
    printf(">> Cliente cadastrado com sucesso!\n");
}

void Imprime_clientes(RegistroCliente *ponteiro) {
    if (ponteiro == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    RegistroCliente *atual = ponteiro;
    while (atual != NULL) {
        printf("----- Registro de Clientes -----\n");
        printf("CPF: %lld\n", atual->CPF);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Telefone: %lld\n", atual->telefone);
        printf("Data de Nascimento: %d\n", atual->data_de_nascimento);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

RegistroCliente *buscaCPF(RegistroCliente *ponteiro, long long int CPF) {
    RegistroCliente *atual = ponteiro;
    while (atual != NULL) {
        if (atual->CPF == CPF) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void Menu_produtos() {
    int opcao;
    do {
        printf("\n=== PRODUTOS ===\n");
        printf("0. Voltar\n");
        scanf("%d", &opcao);
    } while (opcao != 0);
}

void Menu_compras() {
    int opcao;
    do {
        printf("\n=== CARRINHO ===\n");
        printf("0. Voltar\n");
        scanf("%d", &opcao);
    } while (opcao != 0);
}