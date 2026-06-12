#ifndef SISTEMA_H
#define SISTEMA_H

#include "lista.h"
#include "pilha.h"

/* Imprime o cabecalho do sistema no terminal. */
void exibir_cabecalho(void);

/* Exibe o menu principal e retorna a opcao escolhida pelo usuario. */
int exibir_menu(void);

/* Funcoes de cada operacao do menu. */
void menu_cadastrar(ListaLivros *catalogo, PilhaHistorico *historico);
void menu_remover(ListaLivros *catalogo, PilhaHistorico *historico);
void menu_buscar(ListaLivros *catalogo);
void menu_emprestar(ListaLivros *catalogo, PilhaHistorico *historico);
void menu_devolver(ListaLivros *catalogo, PilhaHistorico *historico);

#endif /* SISTEMA_H */
