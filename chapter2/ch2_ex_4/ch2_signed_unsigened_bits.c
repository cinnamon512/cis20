#include <stdio.h>
#include <stdint.h>

static void print8(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        putchar(((x >> i) & 1) ? '1' : '0');
        if (i == 4) putchar(' ');
    }
}

int main(void) {
    uint8_t u = 200;   // 11001000
    uint8_t v = 100;   // 01100100
    uint8_t sum = (uint8_t)(u + v);  // wraps: 200+100=300 -> 44

    // reinterpret the SAME 8 bits as signed
    int8_t sum_signed = (int8_t)sum;

    printf("u        = %3u  0x%02X  ", u, u); print8(u); puts("");
    printf("v        = %3u  0x%02X  ", v, v); print8(v); puts("");

    unsigned true_sum = (unsigned)u + (unsigned)v; // 300
    printf("\ntrue_sum (wider) = %u\n", true_sum);

    printf("sum (uint8_t)     = %3u  0x%02X  ", sum, sum); print8(sum); puts("");
    printf("same bits as int8 = %3d  0x%02X  ", sum_signed, (uint8_t)sum_signed); print8((uint8_t)sum_signed); puts("");

    return 0;
}
