#include <stdio.h>

int main() {
    int x = 10;
    int *p = &x;

    printf("x value      = %d\n", x);
    printf("&x address   = %p\n", (void *)&x);
    printf("p (address)  = %p\n", (void *)p);
    printf("*p (value)   = %d\n", *p);

    return 0;
}

