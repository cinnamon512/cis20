#include <stdio.h>

int main() {
    signed char s = -1;      // 1111 (4-bit idea)
    unsigned char u = s;

    printf("signed = %d\n", s);
    printf("unsigned = %u\n", u);

    return 0;
}
