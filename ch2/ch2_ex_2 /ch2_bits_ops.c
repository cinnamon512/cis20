#include <stdio.h>

void print_binary(unsigned char x) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
}

int main() {
    unsigned char a = 0x69; // 01101001
    unsigned char b = 0x55; // 01010101

    printf("a      = 0x%02X  ", a);
    print_binary(a);
    printf("\n");

    printf("b      = 0x%02X  ", b);
    print_binary(b);
    printf("\n\n");

    printf("~a     = 0x%02X  ", (unsigned char)~a);
    print_binary(~a);
    printf("\n");

    printf("a & b  = 0x%02X  ", a & b);
    print_binary(a & b);
    printf("\n");

    printf("a | b  = 0x%02X  ", a | b);
    print_binary(a | b);
    printf("\n");

    printf("a ^ b  = 0x%02X  ", a ^ b);
    print_binary(a ^ b);
    printf("\n");

    return 0;
}
