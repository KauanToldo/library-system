#include <stdio.h>
#include <string.h>

#include "livro.h"
#include "cores.h"

/* Copia 'origem' para 'destino' respeitando o tamanho do buffer e
   garantindo o terminador nulo, mesmo quando a origem e maior. */
static void copiar_texto(char *destino, const char *origem, size_t tamanho)
{
    if (origem == NULL) {
        destino[0] = '\0';
        return;
    }

    strncpy(destino, origem, tamanho - 1);
    destino[tamanho - 1] = '\0';
}

Livro criar_livro(int codigo, const char *titulo, const char *autor,
                   int ano_publicacao, int quantidade_disponivel)
{
    Livro livro;

    livro.codigo = codigo;
    copiar_texto(livro.titulo, titulo, TAM_TITULO);
    copiar_texto(livro.autor, autor, TAM_AUTOR);
    livro.ano_publicacao = ano_publicacao;
    livro.quantidade_total = quantidade_disponivel;
    livro.quantidade_disponivel = quantidade_disponivel;

    return livro;
}

void exibir_livro(const Livro *livro)
{
    if (livro == NULL) {
        return;
    }

    printf(COR_LABEL "  Codigo: " COR_VALOR "%d\n" COR_RESET, livro->codigo);
    printf(COR_LABEL "  Titulo: " COR_VALOR "%s\n" COR_RESET, livro->titulo);
    printf(COR_LABEL "  Autor:  " COR_VALOR "%s\n" COR_RESET, livro->autor);
    printf(COR_LABEL "  Ano:    " COR_VALOR "%d\n" COR_RESET, livro->ano_publicacao);
    printf(COR_LABEL "  Qtd.:   " COR_VALOR "%d\n" COR_RESET, livro->quantidade_disponivel);
}
