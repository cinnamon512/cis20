#include <stdio.h>

int main(void) {
    unsigned char u = 200;
    unsigned char v = 3;

    unsigned char r = u * v;

    printf("u = %u, v = %u\n", u, v);
    printf("u * v (stored) = %u\n", r);

    return 0;
}
