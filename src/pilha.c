#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

void inicializar_pilha(PilhaHistorico *pilha)
{
    pilha->topo = NULL;
}

int empilhar_operacao(PilhaHistorico *pilha, const char *tipo,
                       const char *descricao)
{
    NoPilha *novo = malloc(sizeof(NoPilha));
    if (novo == NULL) {
        return 0;
    }

    strncpy(novo->op.tipo_operacao, tipo, TAM_TIPO_OPERACAO - 1);
    novo->op.tipo_operacao[TAM_TIPO_OPERACAO - 1] = '\0';

    strncpy(novo->op.descricao, descricao, TAM_DESCRICAO - 1);
    novo->op.descricao[TAM_DESCRICAO - 1] = '\0';

    /* Regra LIFO: o no novo passa a ser o topo. */
    novo->abaixo = pilha->topo;
    pilha->topo = novo;

    return 1;
}

void liberar_pilha(PilhaHistorico *pilha)
{
    NoPilha *atual = pilha->topo;

    while (atual != NULL) {
        NoPilha *abaixo = atual->abaixo;
        free(atual);
        atual = abaixo;
    }

    pilha->topo = NULL;
}
