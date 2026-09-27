#include <stdio.h>
#include <stddef.h>

/* Treat any address as a pointer to bytes */
typedef unsigned char *pointer;

/* Print the byte representation of data */
void show_bytes(pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%p\t0x%.2x\n", start + i, start[i]);
    }
    printf("\n");
}

int main(void) {

    int a = 15213;
    int b = -15213;
    long c = 15213;
    float f = 15213.0f;

    printf("int a = 15213\n");
    show_bytes((pointer)&a, sizeof(int));

    printf("int b = -15213\n");
    show_bytes((pointer)&b, sizeof(int));

    printf("long c = 15213\n");
    show_bytes((pointer)&c, sizeof(long));

    printf("float f = 15213.0\n");
    show_bytes((pointer)&f, sizeof(float));

    return 0;
}
