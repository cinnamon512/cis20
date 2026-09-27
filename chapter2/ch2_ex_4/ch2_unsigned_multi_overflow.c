#include <stdio.h>

int main(void) {
    unsigned char u = 15;   // 4-bit example (max = 15)
    unsigned char v = 14;

    unsigned char r = u * v;

    printf("u = %u, v = %u\n", u, v);
    printf("u * v (stored) = %u\n", r);

    return 0;
}
