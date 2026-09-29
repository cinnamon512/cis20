#include <stdio.h>

int main() {
    unsigned short bits = 0x8000;   // 1000 0000 0000 0000

    printf("As unsigned: %u\n", bits);
    printf("As signed:   %d\n", (short)bits);

    return 0;
}
