#include <stdio.h>
#include <limits.h>

int main(void) {
    signed char a = 100;   // 01100100
    signed char b = 60;    // 00111100
    signed char c = a + b; // overflow happens here

    printf("signed char range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    printf("a + b (true math) = %d\n", (int)a + (int)b);
    printf("c (stored result) = %d\n", c);

    return 0;
}
