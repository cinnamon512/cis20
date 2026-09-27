#include <stdio.h>
#include <stdint.h>

int main(void) {
    int8_t u = -8;   // Tmin
    int8_t v = -8;

    int8_t r = u * v;   // ❌ signed overflow (UB)

    printf("u = %d, v = %d\n", u, v);
    printf("u * v = %d\n", r);

    return 0;
}
