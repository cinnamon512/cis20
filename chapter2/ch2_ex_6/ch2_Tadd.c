#include <stdio.h>
#include <stdint.h>

/* Print binary representation of 8-bit value */
void print_bits(int8_t x) {
    uint8_t ux = (uint8_t)x;   // reinterpret bits as unsigned
    for (int i = 7; i >= 0; i--) {
        printf("%d", (ux >> i) & 1);
    }
}

/* Demonstrate signed addition */
void test_add(int8_t a, int8_t b) {
    int8_t result = a + b;

    printf("-------------------------------------------------\n");
    printf("a = %4d  (", a); print_bits(a); printf(")\n");
    printf("b = %4d  (", b); print_bits(b); printf(")\n");

    printf("a + b = %4d  (", result); print_bits(result); printf(")\n");

    /* Detect overflow manually */
    if ((a > 0 && b > 0 && result < 0))
        printf("** Positive Overflow occurred! **\n");

    if ((a < 0 && b < 0 && result >= 0))
        printf("** Negative Overflow occurred! **\n");
}

int main() {

    printf("Range of int8_t: %d to %d\n\n", INT8_MIN, INT8_MAX);

    /* Case 1: No overflow */
    test_add(40, 50);

    /* Case 2: Positive overflow */
    test_add(100, 60);

    /* Case 3: Negative overflow */
    test_add(-100, -60);

    /* Case 4: Mixed signs (never overflow) */
    test_add(100, -50);

    return 0;
}
