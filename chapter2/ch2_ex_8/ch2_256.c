#include <stdio.h>
#include <stdint.h>
#include <math.h>

static void print_bits8(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        putchar((x >> i) & 1 ? '1' : '0');
        if (i == 7 || i == 3) putchar(' '); // after sign and exponent
    }
}

static const int EXP_BITS  = 4;
static const int FRAC_BITS = 3;
static const int BIAS      = (1 << (EXP_BITS - 1)) - 1; // 7
static const int EXP_MAX   = (1 << EXP_BITS) - 1;       // 15

typedef enum {
    TINY_ZERO,
    TINY_DENORM,
    TINY_NORM,
    TINY_INF,
    TINY_NAN
} tiny_class_t;

typedef struct {
    tiny_class_t cls;
    int s;
    int Exp;   // stored exponent field (0..15)
    int frac;  // stored frac field (0..7)
    int E;     // actual exponent
    double M;  // significand
    double v;  // value (if finite)
} tiny_decoded_t;

static const char* class_name(tiny_class_t c) {
    switch (c) {
        case TINY_ZERO:   return "ZERO";
        case TINY_DENORM: return "DENORM";
        case TINY_NORM:   return "NORM";
        case TINY_INF:    return "INF";
        case TINY_NAN:    return "NaN";
        default:          return "?";
    }
}

static tiny_decoded_t decode_tiny(uint8_t bits) {
    tiny_decoded_t d = {0};

    d.s    = (bits >> 7) & 0x1;
    d.Exp  = (bits >> FRAC_BITS) & ((1 << EXP_BITS) - 1);
    d.frac = bits & ((1 << FRAC_BITS) - 1);

    if (d.Exp == 0) {
        if (d.frac == 0) {
            d.cls = TINY_ZERO;
            d.E = 1 - BIAS;      // convention
            d.M = 0.0;
            d.v = d.s ? -0.0 : 0.0;
        } else {
            d.cls = TINY_DENORM;
            d.E = 1 - BIAS;      // fixed exponent for denormals
            d.M = (double)d.frac / (double)(1 << FRAC_BITS); // 0.xxx
            d.v = (d.s ? -1.0 : 1.0) * d.M * ldexp(1.0, d.E);
        }
        return d;
    }

    if (d.Exp == EXP_MAX) {
        if (d.frac == 0) {
            d.cls = TINY_INF;
            d.v = d.s ? -INFINITY : INFINITY;
        } else {
            d.cls = TINY_NAN;
            d.v = NAN;
        }
        return d;
    }

    d.cls = TINY_NORM;
    d.E = d.Exp - BIAS;
    d.M = 1.0 + (double)d.frac / (double)(1 << FRAC_BITS); // 1.xxx
    d.v = (d.s ? -1.0 : 1.0) * d.M * ldexp(1.0, d.E);
    return d;
}

int main(void) {
    printf("Tiny 8-bit float: s(1) exp(4) frac(3), bias=%d\n", BIAS);
    printf("Showing positive-only finite values with spacing Δ = current - previous\n\n");

    printf("%-11s %-5s %-5s %-6s %-8s %-4s %-10s %-14s %-14s\n",
           "bits", "Exp", "frac", "Class", "E", "M", "Value", "Delta", "Note");
    printf("-------------------------------------------------------------------------------------------------\n");

    int positive_only = 1;

    double prev = 0.0;
    int have_prev = 0;
    double prev_delta = -1.0;

    for (int bits = 0; bits < 256; bits++) {
        tiny_decoded_t d = decode_tiny((uint8_t)bits);

        if (positive_only && d.s != 0) continue;

        // Skip NaN/Inf for spacing display (not finite)
        if (d.cls == TINY_INF || d.cls == TINY_NAN) continue;

        // Print bits
        printf("%-11s ", "");
        print_bits8((uint8_t)bits);

        // Exp / frac / class / E
        printf(" %-5d %-5d %-8s %-4d ", d.Exp, d.frac, class_name(d.cls), d.E);

        // Print M in "eighths" form (nice for FRAC_BITS=3)
        // DENORM: M = frac/8
        // NORM:   M = (8+frac)/8
        char mstr[16];
        if (d.cls == TINY_DENORM) {
            snprintf(mstr, sizeof(mstr), "%d/8", d.frac);
        } else if (d.cls == TINY_NORM) {
            snprintf(mstr, sizeof(mstr), "%d/8", (1 << FRAC_BITS) + d.frac);
        } else {
            snprintf(mstr, sizeof(mstr), "0");
        }
        printf("%-10s ", mstr);

        // Value
        printf("%-14.10g ", d.v);

        // Delta (spacing)
        double delta = 0.0;
        char note[32] = "";
        if (!have_prev) {
            // first value shown
            printf("%-14s %-14s\n", "-", "start");
            prev = d.v;
            have_prev = 1;
            continue;
        } else {
            delta = d.v - prev;
            // Mark where spacing changes (e.g., denorm->norm or exponent jumps)
            if (prev_delta < 0.0) {
                // first delta
                snprintf(note, sizeof(note), "first Δ");
            } else if (fabs(delta - prev_delta) > 1e-12) {
                snprintf(note, sizeof(note), "Δ changed");
            } else {
                snprintf(note, sizeof(note), "");
            }

            printf("%-14.10g %-14s\n", delta, note);

            prev = d.v;
            prev_delta = delta;
        }
    }

    printf("\nWhat to look for:\n");
    printf("  • In DENORM region, Δ is constant (equally spaced).\n");
    printf("  • In NORM region, Δ depends on exponent; when E increases by 1, spacing roughly doubles.\n");
    printf("  • The boundary (largest denorm -> smallest norm) should show a continuous step.\n");

    return 0;
}
