#ifndef LISTA_H
#define LISTA_H

#include "livro.h"

/* No da lista encadeada simples que guarda o catalogo. */
typedef struct NoLista
{
    Livro dados;
    struct NoLista *proximo;
} NoLista;

/* Cabecalho da lista: mantem apenas o ponteiro para o primeiro no. */
typedef struct
{
    NoLista *inicio;
} ListaLivros;

/* Deixa a lista pronta para uso (vazia). */
void inicializar_lista(ListaLivros *lista);

/* Insere um livro no fim da lista, preservando a ordem de cadastro.
   Retorna 1 em caso de sucesso e 0 se a alocacao falhar. */
int inserir_livro(ListaLivros *lista, Livro livro);

/* Libera todos os nos e zera o cabecalho da lista. */
void liberar_lista(ListaLivros *lista);

/* Busca um no da lista pelo codigo do livro. Retorna ponteiro para o no ou NULL. */
NoLista *buscar_por_codigo(ListaLivros *lista, int codigo);

/* Busca um livro pelo codigo e retorna ponteiro para os dados ou NULL. */
Livro *buscar_livro_por_codigo(ListaLivros *lista, int codigo);

/* Lista todos os livros do catalogo (imprime usando exibir_livro). */
void listar_livros(const ListaLivros *lista);

/* Remove um livro pelo codigo. Se out_livro for != NULL, copia os dados do
    livro removido para esse ponteiro antes de liberar o no. Retorna 1 se
    removeu com sucesso, 0 caso contrario. */
int remover_por_codigo(ListaLivros *lista, int codigo, Livro *out_livro);

/* Tenta emprestar (decrementar) um exemplar. Retorna 1 em sucesso, 0 se
    nao encontrado ou sem exemplares disponiveis. */
int emprestar_livro(ListaLivros *lista, int codigo);

/* Codigos de retorno de devolver_livro */
#define DEVOLUCAO_OK          1
#define DEVOLUCAO_NAO_ACHADO  0
#define DEVOLUCAO_SEM_DEBITO -1
#define DEVOLUCAO_EXCEDE     -2

/* Registra a devolucao (incrementa quantidade).
   Retorna DEVOLUCAO_OK, DEVOLUCAO_NAO_ACHADO, DEVOLUCAO_SEM_DEBITO ou
   DEVOLUCAO_EXCEDE conforme o caso. */
int devolver_livro(ListaLivros *lista, int codigo);

#endif /* LISTA_H */
