#include <stdio.h>

int main() {
    unsigned int x = 0x12345678;
    unsigned char *p = (unsigned char *)&x;

    for (int i = 0; i < 4; i++)
        printf("%02x ", p[i]);
}
