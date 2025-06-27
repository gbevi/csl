#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    int x = 0;
    int y = 0;
    if ((x < 5)) {
        int y = 10;
    }
    if ((x == 1)) {
        int y = 1;
    }
    else {
        int y = 2;
    }
    if ((x == 1)) {
        int y = 1;
    }
    else if ((x <= 2)) {
        int y = 2;
    }
    else if ((x >= 6)) {
        int y = 4;
    }
    else if ((x > 3)) {
        int y = 8;
    }
    else if (x) {
        int y = 3;
    }
    else if ((x == 1)) {
        int y = (y + x);
    }
    else if ((x == 3)) {
        int y = (y - x);
    }
    return 0;
}
