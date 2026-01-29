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

#endif