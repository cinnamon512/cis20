// iso_demo.c
// Show that signed TAdd_w is: U2T( UAdd_w( T2U(u), T2U(v) ) )

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Print an 8-bit value in binary
static void print_bin8(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        putchar((x >> i) & 1 ? '1' : '0');
        if (i == 4) putchar(' ');
    }
}

// T2U for w=8: same bits, re-interpret as unsigned
static uint8_t T2U8(int8_t t) {
    return (uint8_t)t;
}

// U2T for w=8: same bits, re-interpret as signed
static int8_t U2T8(uint8_t u) {
    return (int8_t)u;
}

// UAdd_w for w=8: unsigned modular addition (wraps mod 256)
static uint8_t UAdd8(uint8_t a, uint8_t b) {
    return (uint8_t)(a + b);
}

// TAdd_w for w=8: two's complement addition as produced by the machine bits
// (In C, signed overflow is UB, so we compute via unsigned and reinterpret.)
static int8_t TAdd8(int8_t a, int8_t b) {
    return U2T8(UAdd8(T2U8(a), T2U8(b)));
}

static void demo_pair(int8_t a, int8_t b) {
    uint8_t au = T2U8(a);
    uint8_t bu = T2U8(b);

    uint8_t u_sum = UAdd8(au, bu);
    int8_t  t_sum = TAdd8(a, b);

    printf("====================================================\n");
    printf("a (int8_t)  = %4" PRId8 "   bits: ", a); print_bin8(au); printf("\n");
    printf("b (int8_t)  = %4" PRId8 "   bits: ", b); print_bin8(bu); printf("\n");

    printf("\nT2U(a)      = %4" PRIu8 "   bits: ", au); print_bin8(au); printf("\n");
    printf("T2U(b)      = %4" PRIu8 "   bits: ", bu); print_bin8(bu); printf("\n");

    printf("\nUAdd(T2U(a),T2U(b)) = %4" PRIu8 "   bits: ", u_sum); print_bin8(u_sum); printf("\n");
    printf("U2T(that)   = %4" PRId8 "   bits: ", U2T8(u_sum)); print_bin8(u_sum); printf("\n");

    printf("\nTAdd(a,b)   = %4" PRId8 "   bits: ", t_sum); print_bin8((uint8_t)t_sum); printf("\n");

    if (t_sum == U2T8(u_sum)) {
        printf("\n✅ Verified: TAdd(a,b) == U2T(UAdd(T2U(a),T2U(b)))\n");
    } else {
        printf("\n❌ Something is wrong (should never happen here)\n");
    }
}

int main(void) {
    // A few illustrative cases:
    demo_pair(-5, 7);      // no overflow
    demo_pair(100, 60);    // positive overflow in int8_t world (wrap)
    demo_pair(-120, -20);  // negative overflow in int8_t world (wrap)
    demo_pair(-128, -1);   // Tmin special case in two's complement

    return 0;
}
