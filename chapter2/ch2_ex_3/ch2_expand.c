#include <stdio.h>

int main(void) {

    /* ---------- Unsigned expansion (zero extension) ---------- */
    unsigned short us = 0x00FF;   // 00000000 11111111 (255)
    unsigned int ui = us;

    printf("Unsigned expansion:\n");
    printf("us = %u\n", us);
    printf("ui = %u\n", ui);
    printf("us hex = 0x%04X\n", us);
    printf("ui hex = 0x%08X\n", ui); // unsigned values get zero extension

    printf("\n"); 

    /* ---------- Signed expansion (sign extension) ---------- */
    short ss = -1;                // 0xFFFF (16-bit)
    int si = ss;

    printf("Signed expansion:\n");
    printf("ss = %d\n", ss);
    printf("si = %d\n", si);
    printf("ss hex = 0x%04X\n", (unsigned short)ss);
    printf("si hex = 0x%08X\n", si); //signed values get sign extension

    return 0;
}
