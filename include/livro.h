#ifndef LIVRO_H
#define LIVRO_H

#define TAM_TITULO 100
#define TAM_AUTOR 100

/* Representa um livro do catalogo da biblioteca. */
typedef struct {
    int codigo;
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    int ano_publicacao;
    int quantidade_total;      /* imutavel: total cadastrado originalmente */
    int quantidade_disponivel;
} Livro;

/* Monta um Livro a partir dos dados informados, copiando as strings
   de forma segura (sempre terminadas em '\0'). */
Livro criar_livro(int codigo, const char *titulo, const char *autor,
                   int ano_publicacao, int quantidade_disponivel);

/* Imprime os dados de um livro no formato padrao usado nas listagens. */
void exibir_livro(const Livro *livro);

#endif /* LIVRO_H */
