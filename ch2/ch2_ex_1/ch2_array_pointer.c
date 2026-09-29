#include <stdio.h>

int main() {
    int a[3] = {1, 2, 3};

    printf("a        = %p\n", (void *)a);
    printf("&a[0]    = %p\n", (void *)&a[0]);
    printf("a[1]     = %d\n", a[1]);
    printf("*(a + 1) = %d\n", *(a + 1));

    return 0;
}

