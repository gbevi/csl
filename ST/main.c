// main_teste_impressao.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

int main() {
    printf("--- Testando a impressão de nós FOR..IN e RANGE ---\n");
    enterScope();

    // Símbolos necessários para o teste
    Simbolo* sym_i = inserirNaTabela(current_scope->symbol_table, "i", "int");
    Simbolo* sym_x = inserirNaTabela(current_scope->symbol_table, "x", "int");

    // --- Construindo a AST para: for i in 1..10 { x = i } ---

    // 1. O iterador: 'i'
    NoAST* iterador = criarNoId("i", sym_i);

    // 2. A coleção, que é um RANGE: 1..10
    Value v1; v1.valint = 1;
    Value v10; v10.valint = 10;
    NoAST* range_start = criarNoConst(TIPO_INT, v1);
    NoAST* range_end = criarNoConst(TIPO_INT, v10);
    NoAST* colecao = criarNoRange(range_start, range_end, 0); // 0 = inclusivo (..)

    // 3. O corpo do laço: { x = i }
    NoAST* corpo_for_in = criarNoAssign(sym_x, criarNoId("i", sym_i));

    // 4. O nó FOR_IN completo
    NoAST* no_for_in = criarNoForIn(iterador, colecao, corpo_for_in);

    printf("AST construída. Imprimindo agora:\n\n");

    // --- A CHAMADA DE TESTE ---
    imprimirAST(no_for_in, 0);

    exitScope();
    return 0;
}