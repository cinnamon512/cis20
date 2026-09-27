#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t a = 200;
    uint8_t b = 100;

    uint16_t true_sum = a + b;
    uint8_t wrapped = a + b;

    printf("true sum = %u\n", true_sum);
    printf("stored (8-bit) = %u\n", wrapped);

    return 0;
}
