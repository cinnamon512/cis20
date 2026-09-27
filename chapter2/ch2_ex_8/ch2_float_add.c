#include <stdio.h>

int main() {

    float a = 1e20f;
    float b = 1.0f;

    printf("a = %.0f\n", a);
    printf("b = %.0f\n", b);

    printf("\na + b = %.0f\n", a + b);
    printf("(a + b) - a = %.0f\n", (a + b) - a);

    float x = 0.1f;
    float y = 0.2f;
    float z = x + y;

    printf("\nx = %.10f\n", x);
    printf("y = %.10f\n", y);
    printf("x + y = %.10f\n", z);

    return 0;
}
