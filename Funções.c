#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"

//MENU PRINCIPAL.
void Menu_inicial() {
    int opcao;
    RegistroCliente *lista_clientes = NULL;
    RegistroProduto *lista_produtos = NULL;

    do {
        printf("\n=== MENU INICIAL ===\n");
        printf("1. Gerenciamento de Clientes\n");
        printf("2. Gerenciamento de Produtos\n");
        printf("3. Carrinho de Compras\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Menu_clientes(&lista_clientes); break;
            case 2: Menu_produtos(&lista_produtos); break;
            case 3: Menu_compras(&lista_clientes, &lista_produtos); break;
            case 0: Limpeza_mem(&lista_clientes, &lista_produtos); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//CRUD DOS CLIENTES.
void Menu_clientes(RegistroCliente **ptr_lista_clientes) {
    int opcao;
    do {
        printf("\n=== GERENCIAMENTO DE CLIENTES ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("5. Buscar Cliente pelo CPF\n");
        printf("0. Voltar ao Menu Inicial\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Cadastro_cliente(ptr_lista_clientes); break;
            case 2: Imprime_clientes(*ptr_lista_clientes); break;
            case 3: Editar_cliente(*ptr_lista_clientes); break;
            case 4: Remover_cliente(ptr_lista_clientes); break;
            case 5: {
                long long cpf_busca;
                printf("Digite o CPF: ");
                scanf("%lld", &cpf_busca);
                RegistroCliente *res = buscaCPF(*ptr_lista_clientes, cpf_busca);
                if(res) printf("Encontrado: %s\n", res->nome);
                else printf("Nao encontrado.\n");
                break;
            }
            case 0: printf("\nVoltando... \n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void Cadastro_cliente(RegistroCliente **ptr_lista_clientes) {
    RegistroCliente *novo = malloc(sizeof(RegistroCliente));
    
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

    novo->Item=NULL;

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

void Editar_cliente(RegistroCliente *lista) {
    long long int cpf_busca;
    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Digite o CPF do cliente que deseja editar: ");
    scanf("%lld", &cpf_busca);

    RegistroCliente *alvo = buscaCPF(lista, cpf_busca);

    if (alvo == NULL) {
        printf("Erro: Cliente com CPF %lld nao encontrado.\n", cpf_busca);
        return;
    }

    int opcao_edicao;
    do {
        printf("\nEditando Cliente: %s\n", alvo->nome);
        printf("1. Alterar Nome\n");
        printf("2. Alterar Email\n");
        printf("3. Alterar Telefone\n");
        printf("4. Alterar Data de Nascimento\n");
        printf("0. Finalizar Edicao\n");

        scanf("%d", &opcao_edicao);

        switch(opcao_edicao) {
            case 1: {
                printf("Nome atual: %s\n", alvo->nome);
                printf("Novo nome: ");

                free(alvo->nome); 
                alvo->nome = (char*) malloc(100 * sizeof(char));
                scanf(" %[^\n]", alvo->nome);
                printf(">> Nome atualizado!\n");
                break;
            }
            case 2: {
                printf("Email atual: %s\n", alvo->email);
                printf("Novo email: ");
                free(alvo->email);
                alvo->email = (char*) malloc(100 * sizeof(char));
                scanf(" %s", alvo->email);
                printf(">> Email atualizado!\n");
                break;
            }
            case 3: {
                printf("Telefone atual: %lld\n", alvo->telefone);
                printf("Novo telefone: ");
                scanf("%lld", &alvo->telefone);
                printf(">> Telefone atualizado!\n");
                break;
            }
            case 4: {
                printf("Data Nasc. atual: %d\n", alvo->data_de_nascimento);
                printf("Nova data (DDMMAAAA): ");
                scanf("%d", &alvo->data_de_nascimento);
                printf(">> Data atualizada!\n");
                break;
            }
            case 0: printf("Edicao concluida.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao_edicao != 0);
}

void Remover_cliente(RegistroCliente **ptr_lista_clientes) {
    long long cpf_rem;
    printf("Digite o CPF do cliente para remover: ");
    scanf("%lld", &cpf_rem);

    RegistroCliente *atual = *ptr_lista_clientes;
    RegistroCliente *anterior = NULL;

    while (atual != NULL && atual->CPF != cpf_rem) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    if (anterior == NULL) *ptr_lista_clientes = atual->proximo;
    else anterior->proximo = atual->proximo;

    Carrinho *itemAt = atual->Item;
    while (itemAt != NULL) {
        Carrinho *temp = itemAt;
        itemAt = itemAt->proximo;
        free(temp);
    }

    free(atual->nome);
    free(atual->email);
    free(atual);

    printf(">> Cliente removido com sucesso!\n");
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

//CRUD PRODUTOS
void Menu_produtos(RegistroProduto **ptr_lista_produtos) {
    int opcao;

    do {
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produto\n");
        printf("3. Editar Produto\n");
        printf("4. Remover Produto\n");
        printf("5. Buscar Produto pelo Código\n");
        printf("0. Voltar ao Menu Inicial\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Cadastro_produto(ptr_lista_produtos); break;
            case 2: Imprime_produtos(*ptr_lista_produtos); break;
            case 3: Editar_produto(*ptr_lista_produtos); break;
            case 4: Remover_produto(ptr_lista_produtos); break;
            case 5: {
                long long codigo_busca;
                printf("Digite o Código do Produto: ");
                scanf("%lld", &codigo_busca);
                RegistroProduto *res = buscaCodigoUnico(*ptr_lista_produtos, codigo_busca);
                if(res) printf("Encontrado: %s\n", res->nome);
                else printf("Nao encontrado.\n");
                break;
            }
            case 0: printf("\nVoltando... \n"); break;
            default: printf("Opcao invalida!\n");
        } 
    } while (opcao != 0);
}

void Cadastro_produto(RegistroProduto **ptr_lista_produtos) {
    RegistroProduto *novo = (RegistroProduto*) malloc(sizeof(RegistroProduto));
    
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("Digite o Código do Produto: ");
    scanf("%lld", &novo->codigo_unico);
    
    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf(" %[^\n]", novo->nome); 
    
    printf("Digite o preço: ");
    scanf(" %f", &novo->preco);
    
    printf("Digite a quantidade em estoque: ");
    scanf("%lld", &novo->quantidade_estoque);

    novo->proximo = *ptr_lista_produtos;
    *ptr_lista_produtos = novo;
    
    printf(">> Produto cadastrado com sucesso!\n");
}

void Imprime_produtos(RegistroProduto *ponteiro) {
    if (ponteiro == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    RegistroProduto *atual = ponteiro;
    while (atual != NULL) {
        printf("----- Registro de Produtos -----\n");
        printf("Código: %lld\n", atual->codigo_unico);
        printf("Nome: %s\n", atual->nome);
        printf("Preço: %.2f\n", atual->preco);
        printf("Quantidade em estoque: %lld\n", atual->quantidade_estoque);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

void Editar_produto(RegistroProduto *lista) {
    long long int codigo_busca;
    printf("\n--- EDITAR PRODUTO ---\n");
    printf("Digite o Codigo do produto: ");
    scanf("%lld", &codigo_busca);

    RegistroProduto *alvo = buscaCodigoUnico(lista, codigo_busca);

    if (alvo == NULL) {
        printf("Erro: Produto nao encontrado.\n");
        return;
    }

    int opcao_edicao;
    do {
        printf("\nEditando Produto: %s (R$ %.2f)\n", alvo->nome, alvo->preco);
        printf("1. Alterar Nome\n");
        printf("2. Alterar Preco\n");
        printf("3. Alterar Estoque\n");
        printf("0. Finalizar Edicao\n");
        scanf("%d", &opcao_edicao);

        switch(opcao_edicao) {
            case 1: {
                printf("Nome atual: %s\n", alvo->nome);
                printf("Novo nome: ");
                free(alvo->nome);
                alvo->nome = (char*) malloc(50 * sizeof(char));
                scanf(" %[^\n]", alvo->nome);
                break;
            }
            case 2: {
                printf("Preco atual: %.2f\n", alvo->preco);
                printf("Novo preco: ");
                scanf("%f", &alvo->preco);
                break;
            }
            case 3: {
                printf("Estoque atual: %lld\n", alvo->quantidade_estoque);
                printf("Novo estoque: ");
                scanf("%lld", &alvo->quantidade_estoque);
                break;
            }
        }
    } while (opcao_edicao != 0);
    printf(">> Produto atualizado!\n");
}

void Remover_produto(RegistroProduto **ptr_lista_produtos) {
    long long cod_rem;
    printf("Digite o Código do produto para remover: ");
    scanf("%lld", &cod_rem);

    RegistroProduto *atual = *ptr_lista_produtos;
    RegistroProduto *anterior = NULL;

    while (atual != NULL && atual->codigo_unico != cod_rem) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Produto com código %lld nao encontrado.\n", cod_rem);
        return;
    }

    if (anterior == NULL) *ptr_lista_produtos = atual->proximo; 
    else anterior->proximo = atual->proximo;

    if (atual->nome != NULL) free(atual->nome);
    free(atual);

    printf(">> Produto removido com sucesso!\n");
}

RegistroProduto *buscaCodigoUnico(RegistroProduto *ponteiro, long long int codigo_unico) {
    RegistroProduto *atual = ponteiro;
    while (atual != NULL) {
        if (atual->codigo_unico == codigo_unico) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

//CARRINHO.
void Menu_compras(RegistroCliente **ptr_lista_clientes, RegistroProduto **ptr_lista_produtos) {
    int opcao;
    do {
        printf("\n=== CARRINHO ===\n");
        printf("0. Voltar\n");
        scanf("%d", &opcao);
    } while (opcao != 0);
}


//ALOCACAO DE MEMORIA (LIMPEZA)
void Limpeza_mem(RegistroCliente **ptr_clientes, RegistroProduto **ptr_produtos) {
    RegistroCliente *atualCliente = *ptr_clientes;
    while (atualCliente != NULL) {
        RegistroCliente *auxCliente = atualCliente;
        Carrinho *itemAtual = atualCliente->Item;
        while (itemAtual != NULL) {
            Carrinho *itemAux = itemAtual;
            itemAtual = itemAtual->proximo;
            free(itemAux);
        }
        atualCliente = atualCliente->proximo;

        if (auxCliente->nome != NULL) free(auxCliente->nome);
        if (auxCliente->email != NULL) free(auxCliente->email);
        free(auxCliente);
    }

    RegistroProduto *atualProduto = *ptr_produtos;
    while (atualProduto != NULL) {
        RegistroProduto *auxProduto = atualProduto;
        atualProduto = atualProduto->proximo;
        if (auxProduto->nome !=NULL) free(auxProduto->nome);
        free(auxProduto);
    }
    
    *ptr_clientes = NULL;
    *ptr_produtos = NULL;

    printf("\n>> Memoria liberada. Encerrando programa. \n");
}