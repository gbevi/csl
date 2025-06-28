// teste.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "code_generator.h"

int main() {
    // 1) Cria símbolo 'x' e nó ID
    Simbolo* sym_x = malloc(sizeof(Simbolo));
    strcpy(sym_x->nome, "x");
    NoAST* var_x = criarNoId("x", sym_x);

    // 2) Cria nós RETURN para os casos
    NoAST* ret1 = criarNoReturn(criarNoConst(TIPO_INT, (Value){.valint = 1}));
    NoAST* ret2 = criarNoReturn(criarNoConst(TIPO_INT, (Value){.valint = 2}));
    NoAST* ret0 = criarNoReturn(criarNoConst(TIPO_INT, (Value){.valint = 0}));

    // 3) Monta lista de cases
    NoAST_Case* cases = NULL;
    adicionarCase(&cases, criarNoCase(1, ret1));
    adicionarCase(&cases, criarNoCase(2, ret2));

    // 4) Cria nó SWITCH
    NoAST* switch_node = criarNoSwitch(var_x, cases, ret0);

    // 5) Cria um BASIC_NODE para encadear o switch e o 'return 0;'
    //    i.e. corpo do main = { switch_node; return 0; }
    NoAST* final_return = criarNoReturn(criarNoConst(TIPO_INT, (Value){.valint = 0}));
    NoAST* corpo_seq = criarNo(BASIC_NODE, switch_node, final_return);

    // 6) Cria a definição de função main com esse corpo
    Simbolo* sym_main = malloc(sizeof(Simbolo));
    strcpy(sym_main->nome, "main");
    // Nenhum parâmetro: passamos NULL
    NoAST* func_main = criarNoFuncDef(sym_main, NULL, corpo_seq);

    // 7) Gera todo o código C
    gerarCodigoC(func_main, stdout);

    // 8) Limpeza mínima
    free(sym_x);
    free(sym_main);
    return 0;
}
