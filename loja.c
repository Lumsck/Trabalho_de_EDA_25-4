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
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao = -1; 
        }


        switch (opcao) {
            case 1: Menu_clientes(&lista_clientes, lista_produtos); break;
            case 2: Menu_produtos(&lista_produtos); break;
            case 3: Menu_compras(&lista_clientes, &lista_produtos); break;
            case 0: Limpar_memoria(&lista_clientes, &lista_produtos); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//CRUD DOS CLIENTES.
void Menu_clientes(RegistroCliente **ptr_lista_clientes, RegistroProduto *lista_produtos) {
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
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao = -1; 
        }

        switch (opcao) {
            case 1: Cadastrar_clientes(ptr_lista_clientes); break;
            case 2: Imprimir_clientes(*ptr_lista_clientes); break;
            case 3: Editar_clientes(*ptr_lista_clientes); break;
            case 4: Remover_clientes(ptr_lista_clientes, lista_produtos); break;
            case 5: {
                long long cpf_busca;
                printf("Digite o CPF: ");
                scanf("%11lld", &cpf_busca);
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
    long long cpfTemporario;

    printf("Digite o CPF (somente numeros): ");
    scanf("%11lld", &cpfTemporario);

    if (buscaCPF(*ptr_lista_clientes, cpfTemporario) != NULL) {
        printf("Erro: CPF ja cadastrado.\n");
        return;
    }

    RegistroCliente *novo = malloc(sizeof(RegistroCliente));
    
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    novo->CPF = cpfTemporario;

    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf(" %99[^\n]", novo->nome); 
    
    printf("Digite o email: ");
    novo->email = malloc(100 * sizeof(char));
    scanf(" %99s", novo->email);
    
    printf("Digite o telefone (somente numeros, com DDD): ");
    scanf("%11lld", &novo->telefone);
    
    printf("Digite a data de nascimento (DDMMAAAA): ");
    scanf("%8d", &novo->data_de_nascimento);

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
        printf("CPF: ");
        Formatar_CPF(atual->CPF);

        printf("\nNome: %s\n", atual->nome);

        printf("Email: %s\n", atual->email);
        
        printf("Telefone: ");
        Formatar_Telefone(atual->telefone);
        
        printf("\nData de nascimento: ");
        Formatar_data_nascimento(atual->data_de_nascimento);

        printf("\n---------------------------------\n");
        atual = atual->proximo;
    }
}

void Editar_clientes(RegistroCliente *lista) {
    long long int cpf_busca;
    printf("\n--- EDITAR CLIENTE ---\n");
    printf("Digite o CPF do cliente que deseja editar (somente numeros): ");
    scanf("%11lld", &cpf_busca);

    RegistroCliente *alvo = buscaCPF(lista, cpf_busca);

    if (alvo == NULL) {
        printf("Erro: cliente com CPF ");
        Formatar_CPF(cpf_busca);
        printf(" nao esta cadastrado.");
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

        if (scanf("%d", &opcao_edicao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao_edicao = -1; 
        }

        switch(opcao_edicao) {
            case 1: {
                printf("Nome atual: %s\n", alvo->nome);
                printf("Novo nome: ");
                free(alvo->nome); 
                alvo->nome = (char*) malloc(100 * sizeof(char));
                scanf(" %99[^\n]", alvo->nome);
                printf(">> Nome atualizado!\n");
                break;
            }
            case 2: {
                printf("Email atual: %s\n", alvo->email);
                printf("Novo email: ");
                free(alvo->email);
                alvo->email = (char*) malloc(100 * sizeof(char));
                scanf(" %99s", alvo->email);
                printf(">> Email atualizado!\n");
                break;
            }
            case 3: {
                printf("Telefone atual: ");
                Formatar_Telefone(alvo->telefone);
                printf("\nNovo telefone (apenas numeros, com DDD): ");
                scanf("%11lld", &alvo->telefone);
                printf(">> Telefone atualizado!\n");
                break;
            }
            case 4: {
                printf("Data de nascimento atual: ");
                Formatar_data_nascimento(alvo->data_de_nascimento);
                printf("\nNova data (DDMMAAAA): ");
                scanf("%8d", &alvo->data_de_nascimento);
                printf(">> Data atualizada!\n");
                break;
            }
            case 0: printf("Edicao concluida.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao_edicao != 0);
}

void Remover_clientes(RegistroCliente **ptr_lista_clientes, RegistroProduto *lista_produtos) {
    long long cpf_rem;
    printf("Digite o CPF do cliente para remover: ");
    scanf("%11lld", &cpf_rem);

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
        RegistroProduto *Produto = buscaCodigoUnico(lista_produtos, itemAt->codigo_produto);

        if (Produto != NULL) {
            Produto->quantidade_estoque += itemAt->quantidade;
            printf(">> Estoque devolvido: %lld unidades do produto %lld.\n", itemAt->quantidade, itemAt->codigo_produto);
        } else printf(">> Item %lld descartado (Produto nao existe mais na loja).\n", itemAt->codigo_produto);

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
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao = -1; 
        }

        switch (opcao) {
            case 1: Cadastrar_produtos(ptr_lista_produtos); break;
            case 2: Imprimir_produtos(*ptr_lista_produtos); break;
            case 3: Editar_produtos(*ptr_lista_produtos); break;
            case 4: Remover_produtos(ptr_lista_produtos); break;
            case 5: {
                long long codigo_busca;
                printf("Digite o codigo do produto: ");
                scanf("%20lld", &codigo_busca);
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
    long long codigoTemporario;

    printf("Digite o codigo do produto: ");
    scanf("%20lld", &codigoTemporario);

    if (buscaCodigoUnico(*ptr_lista_produtos, codigoTemporario) != NULL) {
        printf("Erro: codigo de produto ja existe.\n");
        return;
    }

    RegistroProduto *novo = (RegistroProduto*) malloc(sizeof(RegistroProduto));
    
    if (novo == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    novo->codigo_unico = codigoTemporario;
    
    printf("Digite o nome: ");
    novo->nome = malloc(100 * sizeof(char));
    scanf(" %99[^\n]", novo->nome); 
    
    printf("Digite o preco: ");
    scanf(" %20f", &novo->preco);
    
    printf("Digite a quantidade em estoque: ");
    scanf("%20lld", &novo->quantidade_estoque);

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
    scanf("%20lld", &codigo_busca);

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
        if (scanf("%d", &opcao_edicao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao_edicao = -1; 
        }

        switch(opcao_edicao) {
            case 1: {
                printf("Nome atual: %s\n", alvo->nome);
                printf("Novo nome: ");
                free(alvo->nome);
                alvo->nome = (char*) malloc(50 * sizeof(char));
                scanf(" %99[^\n]", alvo->nome);
                break;
            }
            case 2: {
                printf("Preco atual: %.2f\n", alvo->preco);
                printf("Novo preco: ");
                scanf("%20f", &alvo->preco);
                break;
            }
            case 3: {
                printf("Estoque atual: %lld\n", alvo->quantidade_estoque);
                printf("Novo estoque: ");
                scanf("%20lld", &alvo->quantidade_estoque);
                break;
            }
            case 0: printf(">> Produto atualizado!\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao_edicao != 0);
}

void Remover_produtos(RegistroProduto **ptr_lista_produtos) {
    long long cod_rem;
    printf("Digite o codigo do produto para remover: ");
    scanf("%20lld", &cod_rem);

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
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            Limpar_buffer();
            opcao = -1; 
        }

        switch (opcao) {
            case 1: Inserir_carrinho(*ptr_lista_clientes, *ptr_lista_produtos); break;
            case 2: Listar_carrinho(*ptr_lista_clientes, *ptr_lista_produtos); break;
            case 3: Remover_carrinho(*ptr_lista_clientes, *ptr_lista_produtos); break;
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
    scanf("%11lld", &cpf);
    RegistroCliente *cliente = buscaCPF(listaClientes, cpf);
    if (cliente == NULL) {
        printf("Cliente nao cadastrado.\n");
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%20lld", &codigoProduto);
    RegistroProduto *produto = buscaCodigoUnico(listaProdutos, codigoProduto);
    if (produto == NULL) {
        printf("Produto nao cadastrado.\n");
        return;
    }

    printf("Quantidade desejada: ");
    scanf("%20lld", &_quantidade);
    if (_quantidade <= 0) {
        printf("Erro: quantidade invalida. Digite um valor positivo.\n");
        return;
    }
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
    scanf("%11lld", &cpf);
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
            printf("Produto: %s | Quantidade: %lld | Unidade: R$%.2f | Subtotal: R$%.2f\n", Produto->nome, itemAtual->quantidade, Produto->preco, subtotal);
            totalCompra += subtotal;
        } else {
            printf("Produto de codigo: %lld (item excluido do sistema)\n", itemAtual->codigo_produto);
        }
        itemAtual = itemAtual->proximo;
    }
    printf("-----------------------------\n");
    printf("Valor total da compra: R$ %.2f\n", totalCompra);
}

void Remover_carrinho(RegistroCliente *listaClientes, RegistroProduto *listaProdutos) {
    long long cpf, codigo;
    printf("CPF do cliente: ");
    scanf("%11lld", &cpf);
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
    scanf("%20lld", &codigo);

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

    RegistroProduto *produtoEstoque = buscaCodigoUnico(listaProdutos, codigo);
    if (produtoEstoque != NULL) {
        produtoEstoque->quantidade_estoque += atual->quantidade;
        printf(">> %lld unidade(s) devolvida(s) ao estoque!\n", atual->quantidade);
    } else printf(">> Aviso: produto original nao existe mais, estoque nao reposto.\n");

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
void Formatar_data_nascimento(int dataInteira) {
    int dia = dataInteira / 1000000;
    int mes = (dataInteira % 1000000) / 10000;
    int ano = dataInteira % 10000;
    printf("%02d/%02d/%04d", dia, mes, ano);
}

void Formatar_CPF(long long int cpf) {
    int parte1 = cpf / 100000000;
    int parte2 = (cpf / 100000) % 1000;
    int parte3 = (cpf / 100) % 1000;
    int digito = cpf % 100;
    
    printf("%03d.%03d.%03d-%02d", parte1, parte2, parte3, digito);
}

void Formatar_Telefone(long long int telefone) {
    int ddd = telefone / 1000000000;
    int parte1 = (telefone / 10000) % 100000;
    int parte2 = telefone % 10000;                 

    printf("(%02d) %05d-%04d", ddd, parte1, parte2);
}

void Limpar_buffer() {
    int caracterelido;
    while ((caracterelido = getchar()) != '\n' && caracterelido != EOF);
}