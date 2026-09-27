#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint16_t x = 15213;

    printf("x      = %u\n", x);
    printf("x >> 1 = %u\n", x >> 1);
    printf("x >> 4 = %u\n", x >> 4);
    printf("x >> 8 = %u\n", x >> 8);

    return 0;
}
