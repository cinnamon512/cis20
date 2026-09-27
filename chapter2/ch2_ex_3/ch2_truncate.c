#include <stdio.h>

int main() {
    unsigned int a = 65535; //2^16 -1
    unsigned short b = a + 1; // b = (2^16 - 1 + 1) + mod 2^16 = 0 
    printf("b = %u\n\n", b);  // prints 0


    int x = 32768;        // 0x00008000 (32-bit int)
    short y = x;          // truncates to 16 bits: 0x8000

    printf("int   x = %d\n", x);
    printf("short y = %d\n", y);

    printf("\nHex values:\n");
    printf("x = 0x%08X\n", x & 0xFFFFFFFF);
    printf("y = 0x%04X\n", (unsigned short)y);

    return 0;
}
