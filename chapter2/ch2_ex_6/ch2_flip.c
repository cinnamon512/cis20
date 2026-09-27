#include <stdio.h>
#include <limits.h>

// Function to print binary (32-bit)
void print_binary(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int x = 5;

    printf("Original x = %d\n", x);
    printf("Binary of x:          ");
    print_binary(x);

    int bitwise_not = ~x;
    printf("\n~x (bitwise NOT) = %d\n", bitwise_not);
    printf("Binary of ~x:         ");
    print_binary(bitwise_not);

    int neg = -x;
    printf("\n-x (arithmetic neg) = %d\n", neg);
    printf("Binary of -x:         ");
    print_binary(neg);

    int twos_comp = ~x + 1;
    printf("\n~x + 1 = %d\n", twos_comp);
    printf("Binary of ~x + 1:     ");
    print_binary(twos_comp);

    return 0;
}
