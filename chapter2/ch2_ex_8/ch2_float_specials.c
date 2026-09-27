#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

uint32_t f2u(float f) {
    uint32_t u;
    memcpy(&u, &f, sizeof(u));
    return u;
}

void print_bits(uint32_t u) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (u >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
}

void compare(const char* name1, float a,
             const char* name2, float b) {

    uint32_t ua = f2u(a);
    uint32_t ub = f2u(b);

    printf("\nComparing %s and %s\n", name1, name2);

    printf("  %s bits: ", name1);
    print_bits(ua);
    printf("\n");

    printf("  %s bits: ", name2);
    print_bits(ub);
    printf("\n");

    printf("  Float compare:    (%s < %s) = %d\n",
           name1, name2, a < b);

    printf("  Unsigned compare: (ua < ub) = %d\n",
           ua < ub);
}

int main() {

    float neg = -1.0f;
    float pos =  1.0f;

    float pz =  0.0f;
    float nz = -0.0f;

    float den = 1.0e-45f;      // very small (likely denorm)
    float norm = 1.0f;

    float inf = 1.0f/0.0f;
    float nan = 0.0f/0.0f;

    printf("IEEE Float Comparison Demo (Simple)\n");

    // Case 1: Negative vs Positive
    compare("-1.0", neg, "+1.0", pos);

    // Case 2: +0 vs -0
    compare("+0.0", pz, "-0.0", nz);

    // Case 3: Denorm vs Normal
    compare("denorm", den, "normal", norm);

    // Case 4: Normal vs Infinity
    compare("1.0", norm, "+inf", inf);

    // Case 5: NaN
    compare("NaN", nan, "1.0", norm);

    return 0;
}
