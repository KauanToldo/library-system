#include <stdio.h>

#include "lista.h"
#include "pilha.h"
#include "sistema.h"
#include "cores.h"

static void exibir_catalogo(const ListaLivros *catalogo)
{
    exibir_cabecalho();
    printf(COR_TITULO "  CATALOGO DE LIVROS\n\n" COR_RESET);
    listar_livros(catalogo);

    int c;
    printf(COR_AVISO "\n  Pressione Enter para continuar..." COR_RESET);
    while ((c = getchar()) != '\n' && c != EOF);
}

static void exibir_historico_formatado(const PilhaHistorico *historico)
{
    exibir_cabecalho();
    printf(COR_TITULO "  HISTORICO DE OPERACOES\n" COR_RESET);
    printf(COR_BORDA  "  (mais recente primeiro)\n\n" COR_RESET);
    exibir_historico(historico);

    int c;
    printf(COR_AVISO "\n  Pressione Enter para continuar..." COR_RESET);
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    ListaLivros catalogo;
    PilhaHistorico historico;

    inicializar_lista(&catalogo);
    inicializar_pilha(&historico);

    int opcao;
    do
    {
        opcao = exibir_menu();

        switch (opcao)
        {
        case 1: menu_cadastrar(&catalogo, &historico);  break;
        case 2: menu_remover(&catalogo, &historico);    break;
        case 3: menu_buscar(&catalogo);                 break;
        case 4: exibir_catalogo(&catalogo);             break;
        case 5: menu_emprestar(&catalogo, &historico);  break;
        case 6: menu_devolver(&catalogo, &historico);   break;
        case 7: exibir_historico_formatado(&historico); break;
        case 0:
            exibir_cabecalho();
            printf(COR_SUCESSO "  Encerrando o sistema. Ate logo!\n\n" COR_RESET);
            break;
        }
    } while (opcao != 0);

    liberar_lista(&catalogo);
    liberar_pilha(&historico);

    return 0;
}
