#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    printf("%s\n", "For (1..3):");
    for (int i = 1; i <= 3; i++) {
        printf("%s\n", i);
    }
    printf("%s\n", "For (0...2):");
    for (int j = 0; j <= 2; j++) {
        printf("%s\n", j);
    }
    return 0;
}
