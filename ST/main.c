// este código teve auxílio de inteligencia artificial para geração do teste.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

int main() {
    printf("--- 1. Preparando o ambiente ---\n");
    enterScope();

    Simbolo* sym_x = inserirNaTabela(current_scope->symbol_table, "x", "int");
    Simbolo* sym_func = inserirNaTabela(current_scope->symbol_table, "func_retorna_42", "function");
    
    printf("Símbolos registrados.\n\n");
    printf("--- 2. Construindo a AST ---\n");

    // --- Parte A: A DEFINIÇÃO DA FUNÇÃO ---
    // def func_retorna_42() { return 42; }
    Value v42; v42.valint = 42;
    NoAST* no_42 = criarNoConst(TIPO_INT, v42);
    NoAST* no_return = criarNoReturn(no_42); // <<<--- Nó que queremos testar
    NoAST* func_def = criarNoFuncDef(sym_func, NULL, no_return);

    // --- Parte B: O CÓDIGO PRINCIPAL ---
    // x = func_retorna_42();
    NoAST* func_call = criarNoFuncCall(sym_func, NULL);
    NoAST* assign_x = criarNoAssign(sym_x, func_call);

    // --- Parte C: JUNTANDO TUDO ---
    NoAST* programa_completo = criarNo(BASIC_NODE, func_def, assign_x);

    printf("AST construída.\n\n");
    
    // =======================================================
    // ** O TESTE ACONTECE AQUI **
    // =======================================================
    printf("--- Imprimindo a AST para verificação ---\n");
    imprimirAST(programa_completo, 0);
    printf("-----------------------------------------\n\n");
    // =======================================================

    printf("--- 3. Gerando o Código TAC ---\n");
    gerarCodigoTAC(programa_completo);
    printf("Geração de código concluída.\n\n");

    exitScope();
    return 0;
}