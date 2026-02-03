#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu_inicial();
void Menu_clientes(RegistroCliente **ptr_lista_clientes);
void Menu_produtos(RegistroProduto **ptr_lista_produtos);
<<<<<<< HEAD
void Menu_compras(RegistroCliente **ptr_lista_clientes, RegistroProduto **ptr_lista_produtos);

void Cadastro_cliente(RegistroCliente **ptr_lista_clientes);
void Imprime_clientes(RegistroCliente *ponteiro);
RegistroCliente* buscaCPF(RegistroCliente *lista, long long int cpf);

void Cadastro_produto(RegistroProduto **ptr_lista_produtos);
void Imprime_produtos(RegistroProduto *lista);
RegistroProduto* buscaProduto(RegistroProduto *ponteiro, long long int codigo);

void Limpeza_mem(RegistroCliente **ptr_clientes, RegistroProduto **ptr_produtos);
=======
void Menu_compras(RegistroCliente **ptr_lista_clientes, RegistroProduto *lista_produtos);

void Cadastro_cliente(RegistroCliente **ptr_lista_clientes);
void Imprime_clientes(RegistroCliente *lista);
RegistroCliente* Busca_cliente_cpf(RegistroCliente *lista, long long int cpf);

void Cadastro_produto(RegistroProduto **ptr_lista_produtos);
void Imprime_produtos(RegistroProduto *lista);
>>>>>>> origin/Menus,-criação-dos-.c-e-.h-e-o-desenvolvimento-de-algumas-funções

#endif