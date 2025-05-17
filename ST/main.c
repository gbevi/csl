#include <stdio.h>
#include "ast.h"
#include "tabela.h"

int main() {
    inserirSimbolo("a", "int");
    inserirSimbolo("b", "int");
    inserirSimbolo("c", "int");
    inserirSimbolo("x", "int");

    NoAST *a = criarNoId("a", TIPO_INT);
    NoAST *b = criarNoId("b", TIPO_INT);
    NoAST *c = criarNoId("c", TIPO_INT);
    NoAST *x = criarNoId("x", TIPO_INT);

    NoAST *mult = criarNoOp('*', b, c);
    NoAST *soma = criarNoOp('+', a, mult);
    NoAST *atrib = criarNoOp('=', x, soma);

    printf("Código TAC gerado:\n");
    gerarTAC(atrib);

    return 0;
}