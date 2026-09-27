#include <stdio.h>
#include <stdint.h>

int main(void) {
    int32_t a = INT32_MAX;   //  2147483647 = 0x7FFFFFFF
    int32_t b = 1;

    int32_t s = a + b;       // on most machines you'll SEE -2147483648

    printf("a = %11d  0x%08X\n", a, (uint32_t)a);
    printf("b = %11d  0x%08X\n", b, (uint32_t)b);
    printf("s = a+b = %11d  0x%08X\n", s, (uint32_t)s);

    return 0;
}
