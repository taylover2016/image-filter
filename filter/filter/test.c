#include <stdio.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(void)
{
    BYTE a, b, c, tmp;
    a = 0x7f;
    b = 0xff;
    c = 0xf7;
    tmp = a + b + c;
    printf("%i\n", tmp);
    tmp /= 3;
    printf("%i\n", tmp);
    return 0;
}