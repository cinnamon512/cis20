#include <stdio.h>
#include <stdint.h>

int main() {

    unsigned char x = 255;   // a byte
    uint8_t       y = 255;   // 8-bit integer

    printf("x = %u\ny = %u\n", x, y);



    uint8_t a = 255;
    uint8_t b = 1;

    uint8_t c = a + b;
    printf("255 + 1 = %u\n", c);

    return 0;
}
