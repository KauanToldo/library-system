#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "cores.h"

void inicializar_lista(ListaLivros *lista)
{
    lista->inicio = NULL;
}

int inserir_livro(ListaLivros *lista, Livro livro)
{
    NoLista *novo = malloc(sizeof(NoLista));
    if (novo == NULL)
    {
        return 0;
    }

    novo->dados = livro;
    novo->proximo = NULL;

    /* Insercao no fim para manter a ordem de cadastro na listagem. */
    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        NoLista *atual = lista->inicio;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    return 1;
}

void liberar_lista(ListaLivros *lista)
{
    NoLista *atual = lista->inicio;

    while (atual != NULL)
    {
        NoLista *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}

NoLista *buscar_por_codigo(ListaLivros *lista, int codigo)
{
    NoLista *atual = lista->inicio;
    while (atual != NULL)
    {
        if (atual->dados.codigo == codigo)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

Livro *buscar_livro_por_codigo(ListaLivros *lista, int codigo)
{
    NoLista *no = buscar_por_codigo(lista, codigo);
    return no ? &no->dados : NULL;
}

void listar_livros(const ListaLivros *lista)
{
    NoLista *atual = lista->inicio;

    if (atual == NULL)
    {
        printf(COR_AVISO "  Catalogo vazio.\n" COR_RESET);
        return;
    }

    while (atual != NULL)
    {
        exibir_livro(&atual->dados);
        printf(COR_BORDA "  ------------------------------------------\n" COR_RESET);
        atual = atual->proximo;
    }
}

int remover_por_codigo(ListaLivros *lista, int codigo, Livro *out_livro)
{
    NoLista *atual = lista->inicio;
    NoLista *anterior = NULL;

    while (atual != NULL && atual->dados.codigo != codigo)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        return 0; /* nao encontrado */
    }

    if (anterior == NULL)
    {
        /* removendo o primeiro no */
        lista->inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    if (out_livro != NULL)
    {
        *out_livro = atual->dados;
    }

    free(atual);
    return 1;
}

int emprestar_livro(ListaLivros *lista, int codigo)
{
    NoLista *no = buscar_por_codigo(lista, codigo);
    if (no == NULL)
        return 0;
    if (no->dados.quantidade_disponivel <= 0)
        return 0;
    no->dados.quantidade_disponivel -= 1;
    return 1;
}

int devolver_livro(ListaLivros *lista, int codigo)
{
    NoLista *no = buscar_por_codigo(lista, codigo);
    if (no == NULL)
        return DEVOLUCAO_NAO_ACHADO;
    if (no->dados.quantidade_disponivel >= no->dados.quantidade_total)
        return (no->dados.quantidade_disponivel == no->dados.quantidade_total)
               ? DEVOLUCAO_SEM_DEBITO
               : DEVOLUCAO_EXCEDE;
    no->dados.quantidade_disponivel += 1;
    return DEVOLUCAO_OK;
}
