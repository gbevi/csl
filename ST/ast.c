#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static int temp_id = 0;

NoAST *criarNoNum(int val) {
    NoAST *no = malloc(sizeof(NoAST));
    no->valor = val;
    no->nome[0] = '\0';
    no->operador = 0;
    no->esquerda = no->direita = NULL;
    no->tipo = TIPO_INT;
    return no;
}

NoAST *criarNoId(char *nome, Tipo tipo) {
    NoAST *no = malloc(sizeof(NoAST));
    strcpy(no->nome, nome);
    no->operador = 0;
    no->valor = 0;
    no->esquerda = no->direita = NULL;
    no->tipo = tipo;
    return no;
}

NoAST *criarNoOp(Operador op, NoAST *esq, NoAST *dir) {
    NoAST *no = malloc(sizeof(NoAST));
    no->operador = op;
    no->esquerda = esq;
    no->direita = dir;
    no->valor = 0;
    no->nome[0] = '\0';
    no->tipo = TIPO_INT;
    return no;
}

void imprimirAST(NoAST *no) {
    if (!no) return;
    
    if (strlen(no->nome) > 0) {
        printf("%s", no->nome);
    } else if (no->esquerda || no->direita) {
        switch (no->operador) {
            case OP_SOMA: case OP_SUB: case OP_MULT: case OP_DIV:
            case OP_EQ: case OP_NEQ: case OP_LT: case OP_GT:
            case OP_LE: case OP_GE: case OP_AND: case OP_OR:
            case OP_ASSIGN: case OP_SEQ: case OP_COMMA:

                printf("(");
                imprimirAST(no->esquerda);

                switch (no->operador) {
                    case OP_SOMA:      printf(" + "); break;
                    case OP_SUB:       printf(" - "); break;
                    case OP_MULT:      printf(" * "); break;
                    case OP_DIV:       printf(" / "); break;
                    case OP_EQ:        printf(" == "); break;
                    case OP_NEQ:       printf(" != "); break;
                    case OP_LT:        printf(" < "); break;
                    case OP_GT:        printf(" > "); break;
                    case OP_LE:        printf(" <= "); break;
                    case OP_GE:        printf(" >= "); break;
                    case OP_AND:       printf(" && "); break;
                    case OP_OR:        printf(" || "); break;
                    case OP_ASSIGN:    printf(" = "); break;
                    case OP_SEQ:       printf(" ; "); break;
                    case OP_COMMA:     printf(" , "); break;
                }
                imprimirAST(no->direita);
                printf(")");
                break;

            case OP_NOT:
                printf("(!");
                imprimirAST(no->esquerda);
                printf(")");
                break;

            case OP_PRINT:
                printf("print ");
                imprimirAST(no->esquerda);
                break;
            
            case OP_PUTS:
                printf("puts ");
                imprimirAST(no->esquerda);
                break;

            case OP_RETURN:
                printf("return ");
                imprimirAST(no->esquerda);
                break;

            case OP_GETS:
                printf("gets ");
                imprimirAST(no->esquerda);
                break;

            case OP_IF:
                printf("if (");
                imprimirAST(no->esquerda);
                printf(")");
                imprimirAST(no->direita);
                break;
            
            case OP_ELSE:
                printf("else ");
                imprimirAST(no->esquerda);
                break;

            case OP_ELSIF:
                printf("elsif (");
                imprimirAST(no->esquerda);
                printf(")");
                imprimirAST(no->direita);
                break;

            case OP_WHILE:
                printf("while (");
                imprimirAST(no->esquerda);
                printf(")");
                imprimirAST(no->direita);
                break;

            case OP_FOR:
                printf("for (");
                imprimirAST(no->esquerda);
                printf(")");
                imprimirAST(no->direita);
                break;

            case OP_DEF:
                printf("def ");
                imprimirAST(no->esquerda);
                printf(" ");
                imprimirAST(no->direita);
                break;

            case OP_FUNC_CALL:
                imprimirAST(no->esquerda);
                printf("(");
                imprimirAST(no->direita);
                printf(")");
                break;

            case OP_FUNC_CALL_BLOCK:
                imprimirAST(no->esquerda);
                printf("(");
                imprimirAST(no->direita);
                printf(") {...}");
                break;
            
            case OP_ERR:
                printf("erro");
                break;

            default:
                printf("?");
                break;

        }
    } else {
        printf("%d", no->valor);
    }
}

char* novaTemp() {
    static char nome[10];
    sprintf(nome, "t%d", temp_id++);
    return strdup(nome);
}

char* gerarTAC(NoAST *no) {
    if (!no) return NULL;

    if (!no->esquerda && !no->direita) {
        if (strlen(no->nome) > 0) return strdup(no->nome);
        char *tmp = malloc(10);
        sprintf(tmp, "%d", no->valor);
        return tmp;
    }

    char *esq = gerarTAC(no->esquerda);
    char *dir = gerarTAC(no->direita);
    char *tmp = novaTemp();

    char op[4];
    switch (no->operador) {
        case OP_SOMA: strcpy(op, "+"); break;
        case OP_SUB: strcpy(op, "-"); break;
        case OP_MULT: strcpy(op, "*"); break;
        case OP_DIV: strcpy(op, "/"); break;
        case OP_EQ:  strcpy(op, "=="); break;
        case OP_NEQ: strcpy(op, "!="); break;
        case OP_LT:  strcpy(op, "<"); break;
        case OP_GT:  strcpy(op, ">"); break;
        case OP_LE:  strcpy(op, "<="); break;
        case OP_GE:  strcpy(op, ">="); break;
        case OP_AND: strcpy(op, "&&"); break;
        case OP_OR:  strcpy(op, "||"); break;
        case OP_ASSIGN: strcpy(op, "="); break;
        default: strcpy(op, "?"); break;
    }

    printf("%s = %s %s %s\n", tmp, esq, op, dir);
    free(esq);
    free(dir);
    return tmp;
}

int tiposCompativeis(Tipo t1, Tipo t2) {
    return t1 == t2;
}
