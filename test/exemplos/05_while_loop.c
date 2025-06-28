#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    int i = 0;
    while ((i < 3)) {
        printf("%d\n", i);
        int i = (i + 1);
    }
    return 0;
}
