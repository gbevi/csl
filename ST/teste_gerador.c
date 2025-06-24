// Arquivo: teste_gerador.c
// Finalidade: Driver de teste para o gerador de código, focado no WHILE_NODE.

#include <stdio.h>      // Para a função printf
#include <stdlib.h>     // Para as funções malloc e free
#include <string.h>     // Para a função strcpy

// --- Cabeçalhos do seu projeto ---
#include "ast.h"            // Essencial para todos os tipos e funções da AST (NoAST, criarNo, etc.)
#include "tabela.h"         // Essencial para a definição da struct Simbolo
#include "code_generator.h" // Essencial para a declaração da função gerarCodigoC

int main() {
    printf("--- Iniciando teste do gerador de código para WHILE ---\n\n");

    // Símbolos que vamos usar no teste
    Simbolo* sym_y = malloc(sizeof(Simbolo));
    strcpy(sym_y->nome, "y");

    Simbolo* sym_i = malloc(sizeof(Simbolo));
    strcpy(sym_i->nome, "i");

    // 1. Criar as inicializações: y = 10; i = 0;
    Value val_10; val_10.valint = 10;
    NoAST* assign_y = criarNoAssign(sym_y, criarNoConst(TIPO_INT, val_10));

    Value val_0; val_0.valint = 0;
    NoAST* assign_i = criarNoAssign(sym_i, criarNoConst(TIPO_INT, val_0));

    // Juntar as duas inicializações em uma lista de statements
    NoAST* inicializacoes = criarNo(BASIC_NODE, assign_y, assign_i);


    // 2. Criar a condição do while: i < 3
    Value val_3; val_3.valint = 3;
    NoAST* condicao_while = criarNoRel(OP_REL_LT, criarNoId(sym_i->nome, sym_i), criarNoConst(TIPO_INT, val_3));


    // 3. Criar o corpo do while
    // Primeiro statement do corpo: y = y - 1;
    Value val_1; val_1.valint = 1;
    NoAST* expr_sub = criarNoArithm(OP_SUBTRACAO, criarNoId(sym_y->nome, sym_y), criarNoConst(TIPO_INT, val_1));
    NoAST* stmt1_corpo = criarNoAssign(sym_y, expr_sub);

    // Segundo statement do corpo: i = i + 1;
    NoAST* expr_soma = criarNoArithm(OP_ADICAO, criarNoId(sym_i->nome, sym_i), criarNoConst(TIPO_INT, val_1));
    NoAST* stmt2_corpo = criarNoAssign(sym_i, expr_soma);

    // Juntar os dois statements do corpo em um só bloco
    NoAST* corpo_while = criarNo(BASIC_NODE, stmt1_corpo, stmt2_corpo);


    // 4. Montar o nó WHILE completo
    NoAST* no_while = criarNoWhile(condicao_while, corpo_while);


    // 5. Juntar a inicialização com o laço while para formar o programa completo
    NoAST* raiz_da_ast = criarNo(BASIC_NODE, inicializacoes, no_while);

    printf("AST montada. Gerando código C:\n");
    printf("--------------------------------------\n");

    // Chamar o gerador de código
    gerarCodigoC(raiz_da_ast, stdout);

    printf("--------------------------------------\n");
    printf("\n--- Teste finalizado ---\n");

    free(sym_y);
    free(sym_i);

    return 0;
}