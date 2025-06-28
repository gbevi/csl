#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    int condicao1 = 1;
    int condicao2 = 0;
    int res_and = (condicao1 && condicao2);
    int res_or = (condicao1 || condicao2);
    int res_not = (!condicao1);
    printf("%d\n", res_and);
    printf("%d\n", res_or);
    printf("%d\n", res_not);
    return 0;
}
