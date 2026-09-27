#include <stdio.h>
#include <stdint.h>

int main() {
    printf("=== Unsigned Modular Arithmetic Demo (8-bit) ===\n\n");

    uint8_t a = 250;
    uint8_t b = 10;

    // 1️⃣ Wraparound
    uint8_t sum = a + b;
    printf("Wraparound:\n");
    printf("  %u + %u = %u (mod 256)\n\n", a, b, sum);

    // 2️⃣ Commutative
    uint8_t x = 25;
    uint8_t y = 100;
    printf("Commutative:\n");
    printf("  %u + %u = %u\n", x, y, x + y);
    printf("  %u + %u = %u\n\n", y, x, y + x);

    // 3️⃣ Associative
    uint8_t p = 200;
    uint8_t q = 100;
    uint8_t r = 50;

    uint8_t left = (p + q) + r;
    uint8_t right = p + (q + r);

    printf("Associative:\n");
    printf("  (p + q) + r = %u\n", left);
    printf("  p + (q + r) = %u\n\n", right);

    // 4️⃣ Identity (0)
    uint8_t u = 77;
    printf("Identity:\n");
    printf("  %u + 0 = %u\n\n", u, u + 0);

    // 5️⃣ Additive Inverse
    uint8_t v = 37;
    uint8_t inverse = -v;  // same as 256 - v for uint8_t
    printf("Additive Inverse:\n");
    printf("  v = %u\n", v);
    printf("  -v = %u\n", inverse);
    
    uint8_t result = v + inverse;
    printf("v + (-v) (int result) = %u\n", v + inverse);
    printf("v + (-v) (8-bit result) = %u\n", result);

    return 0;
}
