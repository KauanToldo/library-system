#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

void inicializar_lista(ListaLivros *lista)
{
    lista->inicio = NULL;
}

int inserir_livro(ListaLivros *lista, Livro livro)
{
    NoLista *novo = malloc(sizeof(NoLista));
    if (novo == NULL) {
        return 0;
    }

    novo->dados = livro;
    novo->proximo = NULL;

    /* Insercao no fim para manter a ordem de cadastro na listagem. */
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        NoLista *atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    return 1;
}

void liberar_lista(ListaLivros *lista)
{
    NoLista *atual = lista->inicio;

    while (atual != NULL) {
        NoLista *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}
