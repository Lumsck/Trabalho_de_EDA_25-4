#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Cadastro {
    int CPF;
    char *nome;
    char *email;
    int telefone;
    int data_de_nascimento;
    struct Cadastro * proximo;
} RegistroCliente;

typedef struct Produto {
    int codigo_unico;
    char *nome;
    float preco;
    int quantidade_estoque;
    struct Produto * proximo;
} RegistroProduto;

typedef struct Compra {
    int id_compra;
    int CPF_cliente;
    int codigo_produto;
    int quantidade_comprada;
    float valor_total;
    struct Compra * proximo;
} RegistroCompra;

#endif