# Desenvolvimento de um Sistema de Biblioteca utilizando Estruturas de Dados em C

## Objetivo
O objetivo deste trabalho é aplicar os conceitos estudados na disciplina de Estruturas de Dados I por meio da implementação de um sistema em linguagem C, utilizando:
- Listas encadeadas;
- Pilhas;
- Alocação dinâmica de memória;
- Modularização do código;
- Algoritmos de busca e ordenação *(opcional, visto que não são muito viáveis para listas e pilhas)*.

O sistema deverá permitir o gerenciamento básico de livros de uma biblioteca.

## Descrição do Problema
Uma biblioteca deseja informatizar parte do gerenciamento de seu catálogo de livros. Cada livro deverá possuir as seguintes informações:

- **Código**
- **Título**
- **Autor**
- **Ano de publicação**
- **Quantidade disponível**

O sistema deverá permitir obrigatoriamente: **o cadastro, remoção, busca e listagem de livros**.

A **lista encadeada** deverá ser utilizada para armazenar os livros cadastrados. 
A **pilha** deverá ser utilizada para armazenar o histórico da ordem de retirada dos livros e o histórico das operações realizadas no sistema, por exemplo: *livro cadastrado, livro removido, empréstimo realizado, devolução realizada*.

## Requisitos Obrigatórios
O trabalho deverá obrigatoriamente:
- Ser desenvolvido em linguagem C;
- Utilizar `structs`;
- Utilizar `malloc` e `free` (alocação dinâmica);
- Utilizar lista encadeada implementada manualmente;
- Utilizar pilha implementada manualmente;
- Implementar todas as funcionalidades;
- Possuir modularização em arquivos `.c` e `.h`;
- Compilar sem erros.

---

## O que foi desenvolvido

### Estrutura de arquivos

```
Sistema de Biblioteca/
├── include/
│   ├── livro.h       # Struct Livro e protótipos
│   ├── lista.h       # Struct e funções da lista encadeada
│   ├── pilha.h       # Struct e funções da pilha de histórico
│   ├── sistema.h     # Funções de menu e interação
│   └── cores.h       # Macros de cores ANSI
├── src/
│   ├── livro.c       # criar_livro, exibir_livro
│   ├── lista.c       # Inserção, busca, listagem, remoção, empréstimo, devolução
│   ├── pilha.c       # empilhar_operacao, exibir_historico, liberar_pilha
│   ├── sistema.c     # Menu navegável, leitura de input, operações do usuário
│   └── main.c        # Ponto de entrada e loop principal
└── README.md
```

### Funcionalidades implementadas

- **Cadastrar livro** — com validação de código duplicado, ano (entre 1 e o ano atual) e quantidade (não negativa)
- **Remover livro** — busca por código e libera o nó com `free`
- **Buscar livro** — busca por código e exibe os dados
- **Listar livros** — exibe todo o catálogo em ordem de cadastro
- **Emprestar livro** — decrementa `quantidade_disponivel`; bloqueia se não houver exemplares
- **Devolver livro** — incrementa `quantidade_disponivel`; bloqueia se nenhum exemplar estiver emprestado
- **Histórico de operações** — pilha LIFO com todas as ações realizadas, exibidas da mais recente para a mais antiga, com cores por tipo de operação

### Destaques técnicos

- Menu interativo navegável com setas do teclado ou W/S, seleção com Enter
- Cores ANSI no terminal para erros, sucesso, prompts e histórico
- Entradas inválidas repetem o campo sem encerrar o processo
- `liberar_lista` e `liberar_pilha` garantem que não há memory leaks ao encerrar

## Como compilar e executar

**Compilar:**
```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/livro.c src/lista.c src/pilha.c src/sistema.c -o library_system.exe
```

**Executar:**
```bash
./library_system.exe
```