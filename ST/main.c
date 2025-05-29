#include <stdio.h>
#include "ast.h"
#include "tabela.h"

int main() {
    // Inserindo variáveis na tabela de símbolos
    inserirSimbolo("a", "int");
    inserirSimbolo("b", "int");
    inserirSimbolo("c", "int");
    inserirSimbolo("x", "int");
    inserirSimbolo("i", "int");  // necessário para o while

    // Criando nós da AST para: x = a + (b * c)
    NoAST *a = criarNoId("a", TIPO_INT);
    NoAST *b = criarNoId("b", TIPO_INT);
    NoAST *c = criarNoId("c", TIPO_INT);
    NoAST *x = criarNoId("x", TIPO_INT);

    NoAST *mult = criarNoOp(OP_MULT, b, c);        // b * c
    NoAST *soma = criarNoOp(OP_SOMA, a, mult);     // a + (b * c)
    NoAST *atrib = criarNoOp(OP_ASSIGN, x, soma);  // x = a + (b * c)

    // Criando while: while (i < 10) { print(i); }
    NoAST *cond = criarNoOp(OP_LT, criarNoId("i", TIPO_INT), criarNoNum(10));
    NoAST *corpo = criarNoPrint(criarNoId("i", TIPO_INT));
    NoAST *loop = criarNoOp(OP_WHILE, cond, corpo);

    // Junta os dois com OP_SEQ: (x = a + b * c; while ...)
    NoAST *bloco = criarNoOp(OP_SEQ, atrib, loop);

    

    // Verificação semântica
    printf("Verificando semântica...\n");
    Tipo tipo = verificarSemantica(bloco);

    if (tipo != TIPO_ERRO) {
        printf("Semântica válida.\n");
        printf("Código TAC:\n");
        gerarTAC(bloco);
    } else {
        printf("Erro semântico detectado.\n");
    }

    return 0;
}
