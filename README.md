# Trabalho prático de EDA 1 - Listas encadeadas em C 

<p align="center">
    <img alt="Static Badge" src="https://img.shields.io/badge/Estado-Finalizado-%2385D100?style=flat">
    <img alt="Static Badge" src="https://img.shields.io/badge/Linguagem-C-%235eccf7?style=flat">
</p>

Sistema de gerenciamento de dados em **C** utilizando **listas simplesmente encadeadas**. O código implementa alocação dinâmica e cobre todo o ciclo de operações CRUD (Inserir, Consultar, Atualizar e Remover). Desenvolvido para a matéria de Estrutura de Dados 1 na Universidade de Brasília (UnB), ministrada pelo professor: Lucas Ursulino Boaventura.

----

## Estrutura do Projeto

* `main.c`: Ponto de entrada do sistema. Gerencia o menu principal e a inicialização das listas.
* `loja.c`: Implementação de todas as funções, lógica de ponteiros e manipulação das listas encadeadas.
* `loja.h`: Cabeçalho com as definições das `structs`, protótipos das funções e bibliotecas.

----

## Como Executar

Para rodar o projeto, você precisa de um compilador C (como o **GCC**) instalado em sua máquina.

### 🐧 Linux e macOS

Abra o terminal na pasta do projeto e execute:

```bash
# 1. Compilar
gcc main.c loja.c -o loja

# 2. Executar
./loja
```

### 🪟 Windows

No terminal (CMD ou PowerShell):

```bash
# 1. Compilar
gcc main.c loja.c -o loja.exe

# 2. Executar
.\loja.exe
```

----

## Membros do projeto:

<table>
    <tr>
    <td align="center"><a href="https://github.com/Lumsck"><img src="https://avatars.githubusercontent.com/u/86811460?v=4" width="200px;" alt=""/><br/><sub><b>Lucas Marconi Licks</b></sub></a><br/>
    <td align="center"><a href="https://github.com/Patrickrsr"><img src="https://avatars.githubusercontent.com/u/106122246?v=4" width="200px;" alt=""/><br/><sub><b>Patrick Rafael</b></sub></a><br/>
</table>