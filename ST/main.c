#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

int main() {
    printf("--- 1. Preparando o ambiente ---\n");
    enterScope();
    Simbolo* sym_a = inserirNaTabela(current_scope->symbol_table, "a", "int");
    Simbolo* sym_b = inserirNaTabela(current_scope->symbol_table, "b", "int");
    Simbolo* sym_x = inserirNaTabela(current_scope->symbol_table, "x", "int");
    printf("Símbolos registrados.\n\n");

    printf("--- 2. Construindo a AST ---\n");

    // Condição Esquerda: a > 0
    NoAST* cond_esq = criarNoRel(OP_REL_GT, criarNoId("a", sym_a), criarNoConst(TIPO_INT, (Value){.valint=0}));
    // Condição Direita: b < 10
    NoAST* cond_dir = criarNoRel(OP_REL_LT, criarNoId("b", sym_b), criarNoConst(TIPO_INT, (Value){.valint=10}));
    // Nó Lógico: cond_esq && cond_dir
    NoAST* cond_logica = criarNoLogic(OP_AND, cond_esq, cond_dir);

    // Corpo do if: { x = 1; }
    NoAST* corpo_if = criarNoAssign(sym_x, criarNoConst(TIPO_INT, (Value){.valint=1}));
    // Nó IF completo
    NoAST* programa_completo = criarNoIfElseChain(IF_NODE, cond_logica, corpo_if, NULL);

    printf("AST construída.\n\n");
    
    printf("--- Imprimindo a AST para verificação ---\n");
    imprimirAST(programa_completo, 0);
    printf("-----------------------------------------\n\n");
    
    printf("--- 3. Gerando o Código TAC ---\n");
    gerarCodigoTAC(programa_completo);
    printf("Geração de código concluída.\n\n");

    exitScope(); 
    return 0;
}