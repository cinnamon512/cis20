#include <stdio.h>
#include <stdint.h>

static void print8(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        putchar(((x >> i) & 1) ? '1' : '0');
        if (i == 4) putchar(' ');
    }
}

int main(void) {
    uint8_t u = 250;  // 11111010
    uint8_t v = 20;   // 00010100

    uint8_t s = (uint8_t)(u + v); // wraps mod 256

    printf("u = %3u  0x%02X  ", u, u); print8(u); puts("");
    printf("v = %3u  0x%02X  ", v, v); print8(v); puts("");

    // show "true sum" using a wider type
    unsigned true_sum = (unsigned)u + (unsigned)v; // 270
    printf("\ntrue_sum (wider) = %u  0x%X\n", true_sum, true_sum);

    printf("u+v in uint8_t    = %3u  0x%02X  ", s, s); print8(s); puts("");

    return 0;
}
