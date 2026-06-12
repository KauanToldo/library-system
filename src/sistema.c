#include <stdio.h>
#include <string.h>
#include <time.h>

#include "sistema.h"
#include "cores.h"

/* ------------------------------------------------------------------ */
/*  Leitura de tecla unica — compativel com Windows (conio) e Linux   */
/* ------------------------------------------------------------------ */

#define TECLA_CIMA 1000
#define TECLA_BAIXO 1001

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static void modo_raw(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode))
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

static void modo_normal(void) {}

static int ler_tecla(void)
{
    int c = _getch();
    if (c == 0 || c == 0xE0)
    {
        int c2 = _getch();
        if (c2 == 0x48)
            return TECLA_CIMA;
        if (c2 == 0x50)
            return TECLA_BAIXO;
        return c;
    }
    if (c == '\r')
        return '\n';
    return c;
}

#else
#include <termios.h>
#include <unistd.h>

static struct termios modo_salvo;

static void modo_raw(void)
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &modo_salvo);
    raw = modo_salvo;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void modo_normal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo_salvo);
}

static int ler_tecla(void)
{
    int c = getchar();
    if (c == '\033')
    {
        int c2 = getchar();
        if (c2 == '[')
        {
            int c3 = getchar();
            if (c3 == 'A')
                return TECLA_CIMA;
            if (c3 == 'B')
                return TECLA_BAIXO;
        }
        return '\033';
    }
    return c;
}
#endif

/* ------------------------------------------------------------------ */
/* Helpers de terminal                                                  */
/* ------------------------------------------------------------------ */

static void limpar_tela(void)
{
    printf("\033[2J\033[H");
}

static void pausar(void)
{
    printf(COR_AVISO "\n  Pressione Enter para continuar..." COR_RESET);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void ler_linha(const char *prompt, char *buf, int tamanho)
{
    printf(COR_AVISO "%s" COR_RESET, prompt);
    if (fgets(buf, tamanho, stdin) == NULL)
    {
        buf[0] = '\0';
        return;
    }
    int len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
}

static int ler_inteiro(const char *prompt)
{
    int valor;
    int c;
    printf(COR_AVISO "%s" COR_RESET, prompt);
    while (scanf("%d", &valor) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf(COR_ERRO "  [Erro] Valor invalido, digite um numero inteiro.\n" COR_RESET);
        printf(COR_AVISO "%s" COR_RESET, prompt);
    }
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return valor;
}

/* ------------------------------------------------------------------ */
/* Cabecalho                                                            */
/* ------------------------------------------------------------------ */

void exibir_cabecalho(void)
{
    limpar_tela();
    printf(COR_TITULO "  SISTEMA DE BIBLIOTECA\n" COR_RESET);
    printf(COR_BORDA "  ========================\n\n" COR_RESET);
}

/* ------------------------------------------------------------------ */
/* Menu navegavel                                                       */
/* ------------------------------------------------------------------ */

int exibir_menu(void)
{
    static const char *itens[] = {
        "Cadastrar livro",
        "Remover livro",
        "Buscar livro por codigo",
        "Listar todos os livros",
        "Emprestar livro",
        "Devolver livro",
        "Historico de operacoes",
        "Sair"};
    static const int retornos[] = {1, 2, 3, 4, 5, 6, 7, 0};
    int n = 8;
    int sel = 0;

    modo_raw();
    printf("\033[?25l"); /* esconde cursor */

    while (1)
    {
        exibir_cabecalho();

        for (int i = 0; i < n; i++)
        {
            if (i == sel)
                printf(COR_SELECIONADO "  > %s\n" COR_RESET, itens[i]);
            else
                printf(COR_ITEM "    %s\n" COR_RESET, itens[i]);
        }

        printf(COR_BORDA "\n  W/S ou setas para navegar  |  Enter para selecionar\n" COR_RESET);

        int tecla = ler_tecla();

        if (tecla == TECLA_CIMA || tecla == 'w' || tecla == 'W')
            sel = (sel - 1 + n) % n;
        else if (tecla == TECLA_BAIXO || tecla == 's' || tecla == 'S')
            sel = (sel + 1) % n;
        else if (tecla == '\n' || tecla == '\r')
            break;
    }

    printf("\033[?25h"); /* mostra cursor */
    modo_normal();
    return retornos[sel];
}

/* ------------------------------------------------------------------ */
/* Operacoes do menu                                                    */
/* ------------------------------------------------------------------ */

void menu_cadastrar(ListaLivros *catalogo, PilhaHistorico *historico)
{
    exibir_cabecalho();
    printf(COR_TITULO "  CADASTRAR LIVRO\n\n" COR_RESET);

    int codigo = ler_inteiro("  Codigo          : ");

    if (buscar_livro_por_codigo(catalogo, codigo) != NULL)
    {
        printf(COR_ERRO "\n  Erro: ja existe um livro com o codigo %d.\n" COR_RESET, codigo);
        pausar();
        return;
    }

    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];

    ler_linha("  Titulo          : ", titulo, TAM_TITULO);
    ler_linha("  Autor           : ", autor, TAM_AUTOR);

    int ano_atual = (int)(time(NULL) / 31557600) + 1970; /* aproximacao rapida */
    {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        if (tm_info)
            ano_atual = tm_info->tm_year + 1900;
    }

    int ano;
    while (1)
    {
        ano = ler_inteiro("  Ano publicacao  : ");
        if (ano > 0 && ano <= ano_atual)
            break;
        printf(COR_ERRO "  [Erro] Ano deve estar entre 1 e %d.\n" COR_RESET, ano_atual);
    }

    int qtd;
    while (1)
    {
        qtd = ler_inteiro("  Qtd. disponivel : ");
        if (qtd >= 0)
            break;
        printf(COR_ERRO "  [Erro] Quantidade nao pode ser negativa.\n" COR_RESET);
    }

    Livro novo = criar_livro(codigo, titulo, autor, ano, qtd);

    if (!inserir_livro(catalogo, novo))
    {
        printf(COR_ERRO "\n  Erro: falha ao alocar memoria.\n" COR_RESET);
        pausar();
        return;
    }

    char desc[TAM_DESCRICAO];
    snprintf(desc, sizeof(desc), "Livro '%s' (cod. %d) cadastrado", titulo, codigo);
    empilhar_operacao(historico, "Cadastro", desc);

    printf(COR_SUCESSO "\n  Livro cadastrado com sucesso!\n" COR_RESET);
    pausar();
}

void menu_remover(ListaLivros *catalogo, PilhaHistorico *historico)
{
    exibir_cabecalho();
    printf(COR_TITULO "  REMOVER LIVRO\n\n" COR_RESET);

    int codigo = ler_inteiro("  Codigo : ");

    Livro removido;
    if (!remover_por_codigo(catalogo, codigo, &removido))
    {
        printf(COR_ERRO "\n  Livro com codigo %d nao encontrado.\n" COR_RESET, codigo);
        pausar();
        return;
    }

    char desc[TAM_DESCRICAO];
    snprintf(desc, sizeof(desc), "Livro '%s' (cod. %d) removido do catalogo", removido.titulo, removido.codigo);
    empilhar_operacao(historico, "Remocao", desc);

    printf(COR_SUCESSO "\n  Livro '%s' removido com sucesso.\n" COR_RESET, removido.titulo);
    pausar();
}

void menu_buscar(ListaLivros *catalogo)
{
    exibir_cabecalho();
    printf(COR_TITULO "  BUSCAR LIVRO\n\n" COR_RESET);

    int codigo = ler_inteiro("  Codigo : ");

    Livro *encontrado = buscar_livro_por_codigo(catalogo, codigo);

    if (encontrado == NULL)
    {
        printf(COR_ERRO "\n  Livro com codigo %d nao encontrado.\n" COR_RESET, codigo);
        pausar();
        return;
    }

    printf("\n");
    exibir_livro(encontrado);
    pausar();
}

void menu_emprestar(ListaLivros *catalogo, PilhaHistorico *historico)
{
    exibir_cabecalho();
    printf(COR_TITULO "  EMPRESTAR LIVRO\n\n" COR_RESET);

    int codigo = ler_inteiro("  Codigo : ");

    Livro *livro = buscar_livro_por_codigo(catalogo, codigo);

    if (livro == NULL)
    {
        printf(COR_ERRO "\n  Livro com codigo %d nao encontrado.\n" COR_RESET, codigo);
        pausar();
        return;
    }

    if (livro->quantidade_disponivel <= 0)
    {
        printf(COR_ERRO "\n  Sem exemplares disponiveis para '%s'.\n" COR_RESET, livro->titulo);
        pausar();
        return;
    }

    emprestar_livro(catalogo, codigo);

    char desc[TAM_DESCRICAO];
    snprintf(desc, sizeof(desc), "Livro '%s' (cod. %d) emprestado", livro->titulo, codigo);
    empilhar_operacao(historico, "Emprestimo", desc);

    printf(COR_SUCESSO "\n  Emprestimo de '%s' realizado.\n" COR_RESET, livro->titulo);
    printf(COR_ITEM "  Exemplares restantes: " COR_VALOR "%d\n" COR_RESET, livro->quantidade_disponivel);
    pausar();
}

void menu_devolver(ListaLivros *catalogo, PilhaHistorico *historico)
{
    exibir_cabecalho();
    printf(COR_TITULO "  DEVOLVER LIVRO\n\n" COR_RESET);

    int codigo = ler_inteiro("  Codigo : ");

    Livro *livro = buscar_livro_por_codigo(catalogo, codigo);

    if (livro == NULL)
    {
        printf(COR_ERRO "\n  Livro com codigo %d nao encontrado.\n" COR_RESET, codigo);
        pausar();
        return;
    }

    int resultado = devolver_livro(catalogo, codigo);

    if (resultado == DEVOLUCAO_SEM_DEBITO || resultado == DEVOLUCAO_EXCEDE)
    {
        printf(COR_ERRO "\n  Nao e possivel devolver: nenhum exemplar de '%s' esta emprestado.\n" COR_RESET,
               livro->titulo);
        pausar();
        return;
    }

    char desc[TAM_DESCRICAO];
    snprintf(desc, sizeof(desc), "Livro '%s' (cod. %d) devolvido", livro->titulo, codigo);
    empilhar_operacao(historico, "Devolucao", desc);

    printf(COR_SUCESSO "\n  Devolucao de '%s' registrada.\n" COR_RESET, livro->titulo);
    printf(COR_ITEM "  Exemplares disponiveis: " COR_VALOR "%d\n" COR_RESET, livro->quantidade_disponivel);
    pausar();
}
