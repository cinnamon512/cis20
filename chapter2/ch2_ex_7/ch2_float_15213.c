#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static void print_bits32(uint32_t u) {
    for (int i = 31; i >= 0; i--) {
        putchar((u >> i) & 1 ? '1' : '0');
        if (i == 31 || i == 23) putchar(' '); // after sign and exponent
    }
}

static uint32_t float_to_u32(float f) {
    uint32_t u;
    memcpy(&u, &f, sizeof(u));
    return u;
}

int main(void) {
    float F = 15213.0f;

    uint32_t bits = float_to_u32(F);

    uint32_t s    = (bits >> 31) & 0x1;
    uint32_t exp  = (bits >> 23) & 0xFF;       // stored exponent field (Exp)
    uint32_t frac = bits & 0x7FFFFF;           // stored fraction field

    const int k = 8;
    const int bias = (1 << (k - 1)) - 1;       // 127 for float
    int E = (int)exp - bias;                   // actual exponent

    // For normalized numbers: M = 1 + frac / 2^23
    double frac_fraction = (double)frac / (double)(1u << 23);
    double M = 1.0 + frac_fraction;

    // v = (-1)^s * M * 2^E
    double v = (s ? -1.0 : 1.0) * M * ldexp(1.0, E);

    printf("F = %.1f\n", F);
    printf("bits: ");
    print_bits32(bits);
    printf("\n");

    printf("s=%u\n", s);
    printf("Exp (stored) = %u (0x%02X)\n", exp, exp);
    printf("Bias = %d\n", bias);
    printf("E = Exp - Bias = %d\n", E);

    printf("frac (stored) = %u (0x%06X)\n", frac, frac);
    printf("frac/2^23 = %.17g\n", frac_fraction);
    printf("M = 1 + frac/2^23 = %.17g\n", M);

    printf("v = (-1)^s * M * 2^E = %.17g\n", v);

    // Quick classification check (optional)
    if (exp == 0) {
        printf("Class: exp==0 (ZERO or DENORMAL)\n");
    } else if (exp == 0xFF) {
        printf("Class: exp==255 (INF or NaN)\n");
    } else {
        printf("Class: NORMALIZED\n");
    }

    return 0;
}
