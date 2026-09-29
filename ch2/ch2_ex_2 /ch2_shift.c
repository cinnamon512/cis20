#include <stdio.h>

int main() {
    unsigned char u = 0x62; // 01100010
    signed char s1 = 0x62;  // positive
    signed char s2 = 0xA2;  // 10100010 (negative)

    printf("u << 3  = 0x%02X\n", u << 3);
    printf("u << 3 (masked) = 0x%02X\n", (u << 3) & 0xFF);

    printf("u >> 2  = 0x%02X (logical)\n", u >> 2);

    printf("s1 >> 2 = 0x%02X (arith)\n", s1 >> 2);

    printf("s2 >> 2 = 0x%02X (arith, sign preserved)\n", s2 >> 2);
    printf("s2 >> 2 (masked) = ox%02X\n", (s2 >> 2) & 0xFF);

    return 0;
}
