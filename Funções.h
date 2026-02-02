#ifndef FUNCOES_H
#define FUNCOES_H

#include "Structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu_inicial();

void Menu_clientes();
void Cadastro_cliente();
void Lista_clientes();
void Edita_cliente();
void Remove_cliente();

void Menu_produtos();
void Cadastro_produto();
void Lista_produtos();
void Edita_produto();
void Remove_produto();

void Menu_compras();
void Realiza_compra();
void Lista_compras();

void Salva_dados();
void Carrega_dados();

#endif