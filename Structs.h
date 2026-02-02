#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Carrinho {
    long long int codigo_produto; 
    int quantidade;
    struct Carrinho * proximo;
} Carrinho;

typedef struct Cadastro {
    long long int CPF;
    char *nome;
    char *email;
    long long int telefone;
    int data_de_nascimento;
    Carrinho * Item;
    struct Cadastro * proximo;
} RegistroCliente;

typedef struct Produto {
    long long int codigo_unico; 
    char *nome;
    float preco;
    int quantidade_estoque;
    struct Produto * proximo;
} RegistroProduto;

#endif