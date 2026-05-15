#include <stdio.h>

#include "livro.h"
#include "lista.h"
#include "pilha.h"
#include "sistema.h"

/* Semana 1: validacao da infraestrutura.
   Inicializa a lista e a pilha, cadastra alguns livros, registra as
   operacoes no historico e libera tudo antes de encerrar. O menu
   interativo entra na Semana 3 do plano. */

static void listar_catalogo(const ListaLivros *lista)
{
    NoLista *atual = lista->inicio;

    if (atual == NULL) {
        printf("Catalogo vazio.\n");
        return;
    }

    while (atual != NULL) {
        exibir_livro(&atual->dados);
        printf("----------------------------------------------\n");
        atual = atual->proximo;
    }
}

static void listar_historico(const PilhaHistorico *pilha)
{
    NoPilha *atual = pilha->topo;

    if (atual == NULL) {
        printf("Nenhuma operacao registrada.\n");
        return;
    }

    while (atual != NULL) {
        printf("[%s] %s\n", atual->op.tipo_operacao, atual->op.descricao);
        atual = atual->abaixo;
    }
}

int main(void)
{
    ListaLivros catalogo;
    PilhaHistorico historico;

    inicializar_lista(&catalogo);
    inicializar_pilha(&historico);

    exibir_cabecalho();

    inserir_livro(&catalogo, criar_livro(1, "O Hobbit", "J.R.R. Tolkien",
                                         1937, 3));
    empilhar_operacao(&historico, "Cadastro",
                      "Livro 'O Hobbit' cadastrado com sucesso");

    inserir_livro(&catalogo, criar_livro(2, "Dom Casmurro",
                                         "Machado de Assis", 1899, 5));
    empilhar_operacao(&historico, "Cadastro",
                      "Livro 'Dom Casmurro' cadastrado com sucesso");

    printf("\nCatalogo de livros:\n");
    printf("----------------------------------------------\n");
    listar_catalogo(&catalogo);

    printf("\nHistorico de operacoes (mais recente primeiro):\n");
    listar_historico(&historico);

    liberar_lista(&catalogo);
    liberar_pilha(&historico);

    return 0;
}
