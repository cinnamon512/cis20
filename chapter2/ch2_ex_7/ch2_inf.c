#include <stdio.h>

int main() {
    double a = 1.0 / 0.0;
    double b = -1.0 / 0.0;

    printf("1.0/0.0 = %f\n", a);
    printf("-1.0/0.0 = %f\n", b);

    return 0;
}
