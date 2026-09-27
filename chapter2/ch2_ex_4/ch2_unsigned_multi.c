#include <stdio.h>

int main(void) {
    unsigned int u = 3;
    unsigned int v = 4;

    unsigned int r = u * v;

    printf("u = %u, v = %u\n", u, v);
    printf("u * v = %u\n", r);

    return 0;
}
