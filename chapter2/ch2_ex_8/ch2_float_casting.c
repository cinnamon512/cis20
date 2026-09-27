#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <float.h>

static void demo_fp_to_int(void) {
    puts("=== double/float -> int (truncate toward 0) ===");

    double d1 = 3.9, d2 = -3.9;
    float  f1 = 3.9f, f2 = -3.9f;

    printf("(int) 3.9        = %d\n", (int)d1);
    printf("(int)-3.9        = %d\n", (int)d2);
    printf("(int) 3.9f       = %d\n", (int)f1);
    printf("(int)-3.9f       = %d\n", (int)f2);

    puts("\n--- Out of range / NaN examples (C says: undefined behavior) ---");
    // Many systems produce INT_MIN for these, but that's NOT guaranteed.
    double huge = 1e300;
    double nanv = NAN;

    // We'll still cast to show what your machine does.
    // WARNING: This is UB by the C standard.
    printf("(int)1e300      = %d   (UB)\n", (int)huge);
    printf("(int)NAN        = %d   (UB)\n", (int)nanv);
}

static void demo_int_to_double(void) {
    puts("\n=== int -> double (exact as long as integer fits in 53 bits) ===");

    int x = INT_MAX;
    double dx = (double)x;

    printf("INT_MAX              = %d\n", x);
    printf("(double)INT_MAX       = %.0f\n", dx);
    printf("Back to int           = %d\n", (int)dx);

    // Show the 53-bit fact using int64_t (since int is usually 32-bit anyway).
    puts("\n--- 53-bit boundary demo using int64_t ---");
    int64_t a = (1LL << 53) - 1; // exactly representable in double
    int64_t b = (1LL << 53);     // exactly representable in double
    int64_t c = (1LL << 53) + 1; // NOT exactly representable in double

    double da = (double)a;
    double db = (double)b;
    double dc = (double)c;

    printf("a = 2^53 - 1 = %lld, (double)a = %.0f, back = %lld\n",
           (long long)a, da, (long long)da);
    printf("b = 2^53     = %lld, (double)b = %.0f, back = %lld\n",
           (long long)b, db, (long long)db);
    printf("c = 2^53 + 1 = %lld, (double)c = %.0f, back = %lld  <-- loses 1\n",
           (long long)c, dc, (long long)dc);
}

static void demo_int_to_float(void) {
    puts("\n=== int -> float (rounding; exact only up to 24 bits of integer precision) ===");

    // 2^24 = 16,777,216 is the point where float can no longer represent every integer.
    int x1 = 16777216; // 2^24
    int x2 = 16777217; // 2^24 + 1 (cannot be represented exactly in float)

    float f1 = (float)x1;
    float f2 = (float)x2;

    printf("x1 = %d, (float)x1 = %.0f\n", x1, f1);
    printf("x2 = %d, (float)x2 = %.0f  <-- rounded (often down to 16777216)\n", x2, f2);

    // Show that consecutive integers collapse to the same float above 2^24
    int x3 = 16777218; // 2^24 + 2 (might be representable, spacing is 2 here)
    float f3 = (float)x3;
    printf("x3 = %d, (float)x3 = %.0f\n", x3, f3);

    puts("\n--- Demonstrate spacing (ULP) around 2^24 ---");
    printf("Nextafterf(16777216 -> +inf) = %.0f\n", nextafterf(16777216.0f, INFINITY));
    printf("Difference (ULP)             = %.0f\n",
           nextafterf(16777216.0f, INFINITY) - 16777216.0f);
}

int main(void) {
    printf("Compiler/Platform info:\n");
    printf("  sizeof(float)  = %zu bytes\n", sizeof(float));
    printf("  sizeof(double) = %zu bytes\n", sizeof(double));
    printf("  sizeof(int)    = %zu bytes\n", sizeof(int));
    printf("  FLT_MANT_DIG   = %d (float precision bits incl. hidden 1)\n", FLT_MANT_DIG);
    printf("  DBL_MANT_DIG   = %d (double precision bits incl. hidden 1)\n", DBL_MANT_DIG);
    puts("");

    demo_fp_to_int();
    demo_int_to_double();
    demo_int_to_float();

    return 0;
}