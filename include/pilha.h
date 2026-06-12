#ifndef PILHA_H
#define PILHA_H

#define TAM_TIPO_OPERACAO 30
#define TAM_DESCRICAO 150

/* Um registro do historico: o que aconteceu e uma breve descricao. */
typedef struct
{
    char tipo_operacao[TAM_TIPO_OPERACAO];
    char descricao[TAM_DESCRICAO];
} Operacao;

/* No da pilha de historico (encadeamento de cima para baixo). */
typedef struct NoPilha
{
    Operacao op;
    struct NoPilha *abaixo;
} NoPilha;

/* Cabecalho da pilha: mantem apenas o ponteiro para o topo. */
typedef struct
{
    NoPilha *topo;
} PilhaHistorico;

/* Deixa a pilha pronta para uso (vazia). */
void inicializar_pilha(PilhaHistorico *pilha);

/* Empilha uma nova operacao no topo do historico (regra LIFO).
   Retorna 1 em caso de sucesso e 0 se a alocacao falhar. */
int empilhar_operacao(PilhaHistorico *pilha, const char *tipo, const char *descricao);

/* Libera todos os nos e zera o cabecalho da pilha. */
void liberar_pilha(PilhaHistorico *pilha);

/* Imprime todas as operacoes do historico (mais recente primeiro). */
void exibir_historico(const PilhaHistorico *pilha);

#endif /* PILHA_H */
