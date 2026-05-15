# Plano do Projeto - Sistema de Biblioteca em C

## 1. Visão Geral do Sistema
O sistema será responsável pelo gerenciamento de livros de uma biblioteca pelo terminal. 
Ele armazenará os dados utilizando duas estruturas de dados principais, alocadas dinamicamente:
1. **Lista Encadeada Simples:** Manterá o catálogo de livros cadastrados na biblioteca, permitindo busca, listagem, remoção e inserção flexível de itens.
2. **Pilha:** Irá armazenar o histórico de todas as operações e movimentações feitas no sistema (como "livro X cadastrado", "livro Y removido", "empréstimo", etc.), operando com a regra LIFO (Last In, First Out). 

## 2. Estrutura de Arquivos

O projeto será modularizado dentro das pastas `src/` (código-fonte) e `include/` (cabeçalhos).

```text
Sistema de Biblioteca/
├── include/
│   ├── livro.h      # Definição e protótipos básicos do que é um Livro
│   ├── lista.h      # Definição das structs e funções da Lista Encadeada
│   ├── pilha.h      # Definição das structs e funções da Pilha (Histórico)
│   └── sistema.h    # Funções de interação do usuário (menus, validações)
├── src/
│   ├── livro.c      # (Opcional) Implementações específicas das regras do livro
│   ├── lista.c      # Implementação de inserção, remoção, busca e listagem
│   ├── pilha.c      # Implementação de push (empilhar) e pop (desempilhar) histórico
│   ├── sistema.c    # Lógica de menus, formatação das saídas, etc.
│   └── main.c       # Ponto de entrada do sistema, loop do menu principal
├── README.md        # Especificações do projeto
└── PLAN.md          # Este documento
```

## 3. Estruturas de Dados (`structs`)

### 3.1. Dados do Livro
```c
typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano_publicacao;
    int quantidade_disponivel;
} Livro;
```

### 3.2. Lista Encadeada (Catálogo)
```c
typedef struct NoLista {
    Livro dados;
    struct NoLista* proximo;
} NoLista;

typedef struct {
    NoLista* inicio;
} ListaLivros;
```

### 3.3. Pilha (Histórico de Operações)
```c
typedef struct {
    char tipo_operacao[30]; // Ex: "Cadastro", "Remoção", "Empréstimo"
    char descricao[150];    // Ex: "Livro 'O Hobbit' cadastrado com sucesso"
} Operacao;

typedef struct NoPilha {
    Operacao op;
    struct NoPilha* abaixo;
} NoPilha;

typedef struct {
    NoPilha* topo;
} PilhaHistorico;
```

## 4. Cronograma de Desenvolvimento (Sextas-feiras)

Como as atividades serão realizadas sempre com foco às sextas-feiras, começando hoje, o cronograma seguirá esta divisão de 3 semanas:

### **Semana 1 - Hoje (Sexta-feira, 15/05/2026)**
**Foco:** Infraestrutura Básica e Estruturas de Dados Modulares.
- [ ] Criação dos arquivos `.h` e `.c` definidos no plano.
- [ ] Definição oficial das `structs` nos `includes`.
- [ ] Implementação da **Lista Encadeada** no arquivo `lista.c` (`inicializar_lista`, `inserir_livro`, alocação correta com `malloc`).
- [ ] Implementação da **Pilha** no arquivo `pilha.c` (`inicializar_pilha`, `empilhar_operacao`, alocação correta de nós).

### **Semana 2 - Próxima (Sexta-feira, 22/05/2026)**
**Foco:** Lógica de Negócios e Funcionalidades Principais.
- [ ] Implementar a função de busca por código dentro da lista encadeada.
- [ ] Implementar a função para listagem completa de todos os livros.
- [ ] Implementar a função e os ponteiros para a remoção de livros e gerenciamento do `free`.
- [ ] Implementar sistema de Empréstimo (decrementa `quantidade_disponivel`) e Devolução (incrementa `quantidade_disponivel`).
- [ ] Integrar as funcionalidades com a Pilha, registrando todo novo cadastro, remoção e empréstimo.

### **Semana 3 - Finalização (Sexta-feira, 29/05/2026)**
**Foco:** Interface com Usuário, Revisão e Testes.
- [ ] Criação do Menu Interativo em `main.c` / `sistema.c`.
- [ ] Funções que coletam input de usuário (ex: `scanf` / `fgets`) utilizando tratamento que evite bugs.
- [ ] Revisão geral do projeto em busca de Memory Leaks (garantir que existe uma função em `lista.c` e `pilha.c` para dar `free` em tudo antes do programa encerrar).
- [ ] Compilação de teste final e criação de eventuais Makefile ou script de execução rápida.
