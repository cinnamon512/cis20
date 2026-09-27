#include <stdio.h>

int main() {
    int x = 5;
    int *p1 = &x;
    int *p2 = NULL;


    if (p1 && *p1)
        printf("p1 safe and nonzero\n");

    if (p2 && *p2)
        printf("won't run\n");

     
    printf("Program did not crash\n");
    return 0;
}
