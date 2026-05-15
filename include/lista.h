#ifndef LISTA_H
#define LISTA_H

#include "livro.h"

/* No da lista encadeada simples que guarda o catalogo. */
typedef struct NoLista {
    Livro dados;
    struct NoLista *proximo;
} NoLista;

/* Cabecalho da lista: mantem apenas o ponteiro para o primeiro no. */
typedef struct {
    NoLista *inicio;
} ListaLivros;

/* Deixa a lista pronta para uso (vazia). */
void inicializar_lista(ListaLivros *lista);

/* Insere um livro no fim da lista, preservando a ordem de cadastro.
   Retorna 1 em caso de sucesso e 0 se a alocacao falhar. */
int inserir_livro(ListaLivros *lista, Livro livro);

/* Libera todos os nos e zera o cabecalho da lista. */
void liberar_lista(ListaLivros *lista);

#endif /* LISTA_H */
