#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MENU INICIAL.
void Menu_inicial();

//CRUD CLIENTES.
void Menu_clientes(RegistroCliente **ptr_lista_clientes);
void Cadastro_cliente(RegistroCliente **ptr_lista_clientes);
void Imprime_clientes(RegistroCliente *ponteiro);
void Editar_cliente(RegistroCliente *lista);
void Remover_cliente(RegistroCliente **ptr_lista_clientes);
RegistroCliente* buscaCPF(RegistroCliente *lista, long long int cpf);

//CRUD PRODUTO.
void Menu_produtos(RegistroProduto **ptr_lista_produtos);
void Cadastro_produto(RegistroProduto **ptr_lista_produtos);
void Imprime_produtos(RegistroProduto *lista);
void Editar_produto(RegistroProduto *lista);
void Remover_produto(RegistroProduto **ptr_lista_produtos);
RegistroProduto *buscaCodigoUnico(RegistroProduto *ponteiro, long long int codigo_unico);

//MENU DE COMPRAS.
void Menu_compras(RegistroCliente **ptr_lista_clientes, RegistroProduto **ptr_lista_produtos);

//ALOCACAO DINAMICA DE MEMORIA.
void Limpeza_mem(RegistroCliente **ptr_clientes, RegistroProduto **ptr_produtos);

#endif