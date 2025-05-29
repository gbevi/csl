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

    NoAST *mult = criarNoOp(OP_MULT, b, c);
    NoAST *soma = criarNoOp(OP_SOMA, a, mult);
    NoAST *atrib = criarNoOp(OP_ASSIGN, x, soma);


    printf("Código TAC gerado:\n");
    gerarTAC(atrib);
    
    printf("Verificando semântica...\n");
    Tipo tipo = verificarSemantica(atrib);

    if (tipo != TIPO_ERRO) {
        printf("Semântica válida.\n");
        printf("Código TAC:\n");
        gerarTAC(atrib);
    } else {
        printf("Erro semântico detectado.\n");
    }

    return 0;
}