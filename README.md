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
**Bom trabalho a todos(as)!**