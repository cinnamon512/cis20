#include <stdio.h>

#define W 8   // universe size {0..7}

/* Print the set represented by x */
void print_set(unsigned char x) {
    printf("{ ");
    for (int i = 0; i < W; i++) {
        if (x & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}");
}

/* Print bits */
void print_bits(unsigned char x) {
    for (int i = W - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
}

int main() {
    unsigned char A = 0b01101001;  // {0,3,5,6}
    unsigned char B = 0b01010101;  // {0,2,4,6}

    printf("A = ");
    print_bits(A);
    printf(" ");
    print_set(A);
    printf("\n");

    printf("B = ");
    print_bits(B);
    printf(" ");
    print_set(B);
    printf("\n\n");

    printf("A & B = ");
    print_bits(A & B);
    printf(" ");
    print_set(A & B);
    printf("\n");

    printf("A | B = ");
    print_bits(A | B);
    printf(" ");
    print_set(A | B);
    printf("\n");

    printf("A ^ B = ");
    print_bits(A ^ B);
    printf(" ");
    print_set(A ^ B);
    printf("\n");

    printf("~A = ");
    print_bits((unsigned char)~A);
    printf(" ");
    print_set((unsigned char)~A);
    printf("\n");

    return 0;
}
