#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));

    *p = 99;
    printf("Value  = %d\n", *p);
    printf("Address= %p\n", (void *)p);

    free(p);
    return 0;
}

