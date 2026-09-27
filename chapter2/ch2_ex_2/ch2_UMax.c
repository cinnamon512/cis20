#include <stdio.h>

int main() {
    unsigned short u;
    short s;

    u = (unsigned short) -1;
    s = -1;

    printf("unsigned short u = %u\n", u);
    printf("signed short   s = %d\n", s);

    printf("u in hex = 0x%04X\n", u);
    printf("s in hex = 0x%04X\n", (unsigned short)s);

    return 0;
}
