#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    for (int item = 0; item <= 5; item++) {
        printf("%d\n", item);
    }
    int i = 0;
    while ((i < 3)) {
        printf("%d\n", i);
        i = (i + 1);
    }
    return 0;
}
