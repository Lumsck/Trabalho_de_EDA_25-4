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
void Cadastrar_clientes(RegistroCliente **ptr_lista_clientes);
void Imprimir_clientes(RegistroCliente *ponteiro);
void Editar_clientes(RegistroCliente *lista);
void Remover_clientes(RegistroCliente **ptr_lista_clientes);
RegistroCliente* buscaCPF(RegistroCliente *lista, long long int cpf);

//CRUD PRODUTO.
void Menu_produtos(RegistroProduto **ptr_lista_produtos);
void Cadastrar_produtos(RegistroProduto **ptr_lista_produtos);
void Imprimir_produtos(RegistroProduto *lista);
void Editar_produtos(RegistroProduto *lista);
void Remover_produtos(RegistroProduto **ptr_lista_produtos);
RegistroProduto *buscaCodigoUnico(RegistroProduto *ponteiro, long long int codigo_unico);

//MENU DE COMPRAS.
void Menu_compras(RegistroCliente **ptr_lista_clientes, RegistroProduto **ptr_lista_produtos);
void Inserir_carrinho(RegistroCliente *listaClientes, RegistroProduto *listaProdutos);
void Listar_carrinho(RegistroCliente *listaClientes, RegistroProduto *listaProdutos);
void Remover_carrinho(RegistroCliente *listaClientes);

//ALOCACAO DINAMICA DE MEMORIA.
void Limpar_memoria(RegistroCliente **ptr_clientes, RegistroProduto **ptr_produtos);

#endif