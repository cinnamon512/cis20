#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define EXP_BITS 3
#define FRAC_BITS 2
#define BIAS ((1 << (EXP_BITS - 1)) - 1)  // 3
#define EXP_MAX ((1 << EXP_BITS) - 1)     // 7

typedef enum { ZERO, DENORM, NORM, INF, NAN_T } fp_class;

typedef struct {
    uint8_t bits;
    int s;
    int Exp;
    int frac;
    int E;
    double M;
    double value;
    fp_class cls;
} tiny6_t;

static void print_bits6(uint8_t x) {
    for (int i = 5; i >= 0; i--) {
        putchar((x >> i) & 1 ? '1' : '0');
        if (i == 5 || i == 2) putchar(' ');
    }
}

static const char* class_name(fp_class c) {
    switch (c) {
        case ZERO:   return "ZERO";
        case DENORM: return "DENORM";
        case NORM:   return "NORM";
        case INF:    return "INF";
        case NAN_T:  return "NaN";
        default:     return "?";
    }
}

static tiny6_t decode(uint8_t bits) {
    tiny6_t d;
    d.bits = bits;
    d.s = (bits >> 5) & 1;
    d.Exp = (bits >> FRAC_BITS) & ((1 << EXP_BITS) - 1);
    d.frac = bits & ((1 << FRAC_BITS) - 1);

    // defaults
    d.E = 0;
    d.M = 0.0;
    d.value = 0.0;
    d.cls = ZERO;

    if (d.Exp == 0) {
        if (d.frac == 0) {
            d.cls = ZERO;
            d.value = d.s ? -0.0 : 0.0;
        } else {
            d.cls = DENORM;
            d.E = 1 - BIAS;
            d.M = (double)d.frac / (1 << FRAC_BITS);          // 0.xx
            d.value = (d.s ? -1.0 : 1.0) * d.M * ldexp(1.0, d.E);
        }
        return d;
    }

    if (d.Exp == EXP_MAX) {
        if (d.frac == 0) {
            d.cls = INF;
            d.value = d.s ? -INFINITY : INFINITY;
        } else {
            d.cls = NAN_T;
            d.value = NAN;
        }
        return d;
    }

    d.cls = NORM;
    d.E = d.Exp - BIAS;
    d.M = 1.0 + (double)d.frac / (1 << FRAC_BITS);            // 1.xx
    d.value = (d.s ? -1.0 : 1.0) * d.M * ldexp(1.0, d.E);
    return d;
}

/* sort by numeric value, with -inf first, +inf near end, NaN last */
static int cmp_by_value(const void *a, const void *b) {
    const tiny6_t *x = (const tiny6_t*)a;
    const tiny6_t *y = (const tiny6_t*)b;

    int x_nan = isnan(x->value), y_nan = isnan(y->value);
    if (x_nan && y_nan) return 0;
    if (x_nan) return 1;
    if (y_nan) return -1;

    // infinities naturally compare in IEEE doubles
    if (x->value < y->value) return -1;
    if (x->value > y->value) return 1;

    // tie-breaker so output is deterministic (e.g., +0 and -0)
    if (x->bits < y->bits) return -1;
    if (x->bits > y->bits) return 1;
    return 0;
}

static int is_finite_fp(const tiny6_t *d) {
    return (d->cls == ZERO || d->cls == DENORM || d->cls == NORM);
}

int main(void) {
    tiny6_t values[64];
    for (int i = 0; i < 64; i++) values[i] = decode((uint8_t)i);

    qsort(values, 64, sizeof(values[0]), cmp_by_value);

    printf("6-bit IEEE-like format: s(1) exp(3) frac(2), bias=%d\n", BIAS);
    printf("Sorted by numeric value. Δ is spacing from previous FINITE value.\n\n");

    printf("%-8s %-4s %-4s %-7s %-12s %-12s %-10s\n",
           "bits", "Exp", "frac", "Class", "Value", "Delta", "Note");
    printf("--------------------------------------------------------------------------\n");

    int have_prev = 0;
    double prev = 0.0;
    double prev_delta = -1.0;

    for (int i = 0; i < 64; i++) {
        tiny6_t d = values[i];

        // print fields
        print_bits6(d.bits);
        printf(" %-4d %-4d %-7s ", d.Exp, d.frac, class_name(d.cls));

        // value string
        char vstr[32];
        if (d.cls == INF) snprintf(vstr, sizeof(vstr), d.value < 0 ? "-inf" : "+inf");
        else if (d.cls == NAN_T) snprintf(vstr, sizeof(vstr), "NaN");
        else if (d.cls == ZERO) snprintf(vstr, sizeof(vstr), signbit(d.value) ? "-0" : "+0");
        else snprintf(vstr, sizeof(vstr), "%.10g", d.value);

        printf("%-12s ", vstr);

        // delta
        char dstr[32] = "-";
        char note[16] = "";

        if (is_finite_fp(&d)) {
            if (!have_prev) {
                have_prev = 1;
                prev = d.value;
                snprintf(note, sizeof(note), "start");
            } else {
                double delta = d.value - prev;
                snprintf(dstr, sizeof(dstr), "%.10g", delta);

                if (prev_delta >= 0.0 && fabs(delta - prev_delta) > 1e-15)
                    snprintf(note, sizeof(note), "Δ change");

                prev = d.value;
                prev_delta = delta;
            }
        } else {
            // INF/NaN: don’t update spacing baseline
            snprintf(note, sizeof(note), "");
        }

        printf("%-12s %-10s\n", dstr, note);
    }

    printf("\nHow to read Δ:\n");
    printf("  • In DENORM region, Δ is constant (equispaced near 0).\n");
    printf("  • In NORM region, Δ is constant within each exponent bucket, but doubles when E increases.\n");
    printf("  • Large |value| => larger spacing.\n");

    return 0;
}
