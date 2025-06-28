#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    int a = 10;
    int b = 5;
    int soma = (a + b);
    int subtracao = (a - b);
    int multiplicacao = (a * b);
    int divisao = (a / b);
    int resultado_complexo = (((a + b) * 2) - divisao);
    printf("%d\n", soma);
    printf("%d\n", subtracao);
    printf("%d\n", multiplicacao);
    printf("%d\n", divisao);
    printf("%d\n", resultado_complexo);
    return 0;
}
