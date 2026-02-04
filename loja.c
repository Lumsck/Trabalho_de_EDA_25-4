#include "loja.h"

//MENU PRINCIPAL.
void Menu_inicial() {
    int opcao;
    RegistroCliente *lista_clientes = NULL;
    RegistroProduto *lista_produtos = NULL;

    do {
        printf("\n=== MENU INICIAL ===\n");
        printf("1. Gerenciamento de clientes\n");
        printf("2. Gerenciamento de produtos\n");
        printf("3. Carrinho de compras\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Menu_clientes(&lista_clientes); break;
            case 2: Menu_produtos(&lista_produtos); break;
            case 3: Menu_compras(&lista_clientes, &lista_produtos); break;
            case 0: Limpar_memoria(&lista_clientes, &lista_produtos); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//CRUD DOS CLIENTES.
void Menu_clientes(RegistroCliente **ptr_lista_clientes) {
    int opcao;
    do {
        printf("\n=== GERENCIAMENTO DE CLIENTES ===\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Editar clientes\n");
        printf("4. Remover clientes\n");
        printf("5. Buscar cliente pelo CPF\n");
        printf("0. Voltar ao menu inicial\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Cadastrar_clientes(ptr_lista_clientes); break;
            case 2: Imprimir_clientes(*ptr_lista_clientes); break;
            case 3: Editar_clientes(*ptr_lista_clientes); break;
            case 4: Remover_clientes(ptr_lista_clientes); break;
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

void Cadastrar_clientes(RegistroCliente **ptr_lista_clientes) {
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

void Imprimir_clientes(RegistroCliente *ponteiro) {
    if (ponteiro == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    RegistroCliente *atual = ponteiro;
    while (atual != NULL) {
        printf("----- Registro de clientes -----\n");
        printf("CPF: %lld\n", atual->CPF);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Telefone: %lld\n", atual->telefone);
        printf("Data de nascimento: %d\n", atual->data_de_nascimento);
        Formatar_data_nascimento(atual->data_de_nascimento);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

void Editar_clientes(RegistroCliente *lista) {
    long long int cpf_busca;
    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Digite o CPF do cliente que deseja editar: ");
    scanf("%lld", &cpf_busca);

    RegistroCliente *alvo = buscaCPF(lista, cpf_busca);

    if (alvo == NULL) {
        printf("Erro: cliente com CPF %lld nao encontrado.\n", cpf_busca);
        return;
    }

    int opcao_edicao;
    do {
        printf("\nEditando cliente: %s\n", alvo->nome);
        printf("1. Alterar nome\n");
        printf("2. Alterar email\n");
        printf("3. Alterar telefone\n");
        printf("4. Alterar data de nascimento\n");
        printf("0. Finalizar edicao\n");

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
                printf("Data de nascimento atual: %d\n", alvo->data_de_nascimento);
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

void Remover_clientes(RegistroCliente **ptr_lista_clientes) {
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
        printf("Erro: cliente nao encontrado.\n");
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
        printf("1. Cadastrar produto\n");
        printf("2. Listar produto\n");
        printf("3. Editar produto\n");
        printf("4. Remover produto\n");
        printf("5. Buscar produto pelo codigo\n");
        printf("0. Voltar ao menu inicial\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Cadastrar_produtos(ptr_lista_produtos); break;
            case 2: Imprimir_produtos(*ptr_lista_produtos); break;
            case 3: Editar_produtos(*ptr_lista_produtos); break;
            case 4: Remover_produtos(ptr_lista_produtos); break;
            case 5: {
                long long codigo_busca;
                printf("Digite o codigo do produto: ");
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

void Cadastrar_produtos(RegistroProduto **ptr_lista_produtos) {
    RegistroProduto *novo = (RegistroProduto*) malloc(sizeof(RegistroProduto));
    
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%lld", &novo->codigo_unico);
    
    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf(" %[^\n]", novo->nome); 
    
    printf("Digite o preco: ");
    scanf(" %f", &novo->preco);
    
    printf("Digite a quantidade em estoque: ");
    scanf("%lld", &novo->quantidade_estoque);

    novo->proximo = *ptr_lista_produtos;
    *ptr_lista_produtos = novo;
    
    printf(">> Produto cadastrado com sucesso!\n");
}

void Imprimir_produtos(RegistroProduto *ponteiro) {
    if (ponteiro == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    RegistroProduto *atual = ponteiro;
    while (atual != NULL) {
        printf("----- REGISTRO DE PRODUTOS -----\n");
        printf("Codigo: %lld\n", atual->codigo_unico);
        printf("Nome: %s\n", atual->nome);
        printf("Preco: %.2f\n", atual->preco);
        printf("Quantidade em estoque: %lld\n", atual->quantidade_estoque);
        printf("-----------------------\n");
        atual = atual->proximo;
    }
}

void Editar_produtos(RegistroProduto *lista) {
    long long int codigo_busca;
    printf("\n--- EDITAR PRODUTO ---\n");
    printf("Digite o codigo do produto: ");
    scanf("%lld", &codigo_busca);

    RegistroProduto *alvo = buscaCodigoUnico(lista, codigo_busca);

    if (alvo == NULL) {
        printf("Erro: produto nao encontrado.\n");
        return;
    }

    int opcao_edicao;
    do {
        printf("\nEditando produto: %s (R$ %.2f)\n", alvo->nome, alvo->preco);
        printf("1. Alterar nome\n");
        printf("2. Alterar preco\n");
        printf("3. Alterar estoque\n");
        printf("0. Finalizar edicao\n");
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

void Remover_produtos(RegistroProduto **ptr_lista_produtos) {
    long long cod_rem;
    printf("Digite o codigo do produto para remover: ");
    scanf("%lld", &cod_rem);

    RegistroProduto *atual = *ptr_lista_produtos;
    RegistroProduto *anterior = NULL;

    while (atual != NULL && atual->codigo_unico != cod_rem) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: produto com codigo %lld nao encontrado.\n", cod_rem);
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
        printf("\n=== MODO COMPRA ===\n");
        printf("1. Adicionar item ao carrinho\n");
        printf("2. Ver o carrinho e total\n");
        printf("3. Remover item do carrinho\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: Inserir_carrinho(*ptr_lista_clientes, *ptr_lista_produtos); break;
            case 2: Listar_carrinho(*ptr_lista_clientes, *ptr_lista_produtos); break;
            case 3: Remover_carrinho(*ptr_lista_clientes); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void Inserir_carrinho(RegistroCliente *listaClientes, RegistroProduto *listaProdutos) {
    long long cpf;
    long long codigoProduto;
    long long _quantidade;

    printf("Digite o CPF do cliente: ");
    scanf("%lld", &cpf);
    RegistroCliente *cliente = buscaCPF(listaClientes, cpf);
    if (cliente == NULL) {
        printf("Cliente nao cadastrado.\n");
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%lld", &codigoProduto);
    RegistroProduto *produto = buscaCodigoUnico(listaProdutos, codigoProduto);
    if (produto == NULL) {
        printf("Produto nao cadastrado.\n");
        return;
    }

    printf("Quantidade desejada: ");
    scanf("%lld", &_quantidade);
    if (_quantidade > produto->quantidade_estoque) {
        printf("Erro: estoque insuficiente (disponivel: %lld)\n", produto->quantidade_estoque);
        return;
    }

    Carrinho *novoItem = malloc(sizeof(Carrinho));
    if (novoItem == NULL) return;

    novoItem->codigo_produto = codigoProduto;
    novoItem->quantidade = _quantidade;
    novoItem->proximo = cliente->Item;
    cliente->Item = novoItem;

    produto->quantidade_estoque -= _quantidade;

    printf(">> Item adicionado ao carrinho de %s!\n", cliente->nome);
}

void Listar_carrinho(RegistroCliente *listaClientes, RegistroProduto *listaProdutos) {
    long long cpf;
    printf("Digite o CPF para ver o carrinho: ");
    scanf("%lld", &cpf);
    RegistroCliente *cliente = buscaCPF(listaClientes, cpf);

    if (cliente == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    
    if (cliente->Item == NULL) {
        printf("O carrinho está vazio.\n");
        return;
    }

    printf("\n--- Carrinho de %s ---\n", cliente->nome);

    Carrinho *itemAtual = cliente->Item;
    float totalCompra = 0.00;

    while (itemAtual != NULL) {
        RegistroProduto *Produto = buscaCodigoUnico(listaProdutos, itemAtual->codigo_produto);
        if (Produto != NULL) {
            float subtotal = Produto->preco * itemAtual->quantidade;
            printf("Produto: %s | Quantidade: %d | Unidade: R$%.2f | Subtotal: R$%.2f\n", Produto->nome, itemAtual->quantidade, Produto->preco, subtotal);
            totalCompra += subtotal;
        } else {
            printf("Produto de codigo: %lld (item excluido do sistema)\n", itemAtual->codigo_produto);
        }
        itemAtual = itemAtual->proximo;
    }
    printf("-----------------------------\n");
    printf("Valor total da compra: R$ %.2f\n", totalCompra);
}

void Remover_carrinho(RegistroCliente *listaClientes) {
    long long cpf, codigo;
    printf("CPF do cliente: ");
    scanf("%lld", &cpf);
    RegistroCliente *cliente = buscaCPF(listaClientes, cpf);
    if (cliente == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    if (cliente->Item == NULL) {
        printf("Carrinho vazio.\n");
        return;
    }
    printf("Codigo do produto para remover: ");
    scanf("%lld", &codigo);

    Carrinho *atual = cliente->Item;
    Carrinho *anterior = NULL;

    while (atual != NULL && atual->codigo_produto != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao esta no carrinho.\n");
        return;
    }

    if (anterior == NULL) cliente->Item = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido do carrinho!\n");
}

//ALOCACAO DE MEMORIA (LIMPEZA)
void Limpar_memoria(RegistroCliente **ptr_clientes, RegistroProduto **ptr_produtos) {
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

//FUNCOES ADICIONAIS
void printDataFormatada(int dataInteira) {
    int dia = dataInteira / 1000000;
    int mes = (dataInteira % 1000000) / 10000;
    int ano = dataInteira % 10000;
    printf("%02d/%02d/%04d", dia, mes, ano);
}