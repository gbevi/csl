#include <stdio.h>
#include <stdlib.h>

int yyparse(void);

extern int tem_erro;

int main(int argc, char **argv) {
    tem_erro = 0;

    int resultado = yyparse();

    if (resultado != 0 || tem_erro) {
        fprintf(stderr, "Parser terminou com erro.\n");
        return 1;
    }

    printf("Parser terminou com sucesso.\n");
    return 0;
}
