#ifndef CORES_H
#define CORES_H

#define COR_RESET      "\033[0m"
#define COR_TITULO     "\033[1;36m"   /* ciano negrito  - cabecalhos        */
#define COR_SUCESSO    "\033[1;32m"   /* verde negrito  - mensagens ok       */
#define COR_ERRO       "\033[1;31m"   /* vermelho       - erros              */
#define COR_AVISO      "\033[1;33m"   /* amarelo        - avisos / prompts   */
#define COR_ITEM       "\033[0;37m"   /* branco normal  - itens do menu      */
#define COR_LABEL      "\033[0;36m"   /* ciano normal   - rotulos do livro   */
#define COR_VALOR      "\033[1;37m"   /* branco negrito - valores do livro   */
#define COR_BORDA      "\033[0;34m"   /* azul           - separadores        */
#define COR_SELECIONADO "\033[1;32m"  /* verde negrito  - item selecionado   */

/* Cores por tipo de operacao no historico */
#define COR_OP_CADASTRO   "\033[1;32m"  /* verde   */
#define COR_OP_REMOCAO    "\033[1;31m"  /* vermelho */
#define COR_OP_EMPRESTIMO "\033[1;33m"  /* amarelo  */
#define COR_OP_DEVOLUCAO  "\033[1;36m"  /* ciano    */
#define COR_OP_PADRAO     "\033[0;37m"  /* branco   */

#endif /* CORES_H */
