#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "ast.h"
#include "tabela.h"
#include <stdio.h>

// essa é a função principal q inicia a geracao de codigo C a partir da AST
void gerarCodigoC(NoAST *raiz, FILE *saida);

#endif