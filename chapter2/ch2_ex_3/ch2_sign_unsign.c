#include <stdio.h>

int main() {
    int x1 = -1;
    int x2 = -2;
    int x3 = 0;

    printf("signed: %d  -> unsigned: %u\n", x1, (unsigned)x1);
    printf("signed: %d  -> unsigned: %u\n", x2, (unsigned)x2);
    printf("signed: %d  -> unsigned: %u\n", x3, (unsigned)x3);

    return 0;
}

