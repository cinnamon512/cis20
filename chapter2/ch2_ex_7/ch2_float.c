#include <stdio.h>
#include <math.h>

int main() {
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;

    printf("=== Basic Printing ===\n");
    printf("0.1  = %.20f\n", a);
    printf("0.2  = %.20f\n", b);
    printf("0.3  = %.20f\n", c);

    printf("\n=== Addition ===\n");
    printf("0.1 + 0.2 = %.20f\n", a + b);

    printf("\n=== Comparison ===\n");
    if (a + b == c)
        printf("0.1 + 0.2 == 0.3 (TRUE)\n");
    else
        printf("0.1 + 0.2 == 0.3 (FALSE)\n");

    printf("\nDifference (a + b - c) = %.20f\n", (a + b - c));

    printf("\n=== Safe Comparison ===\n");
    double epsilon = 1e-15;
    if (fabs((a + b) - c) < epsilon)
        printf("Approximately equal (within epsilon)\n");
    else
        printf("Not approximately equal\n");

    return 0;
}
