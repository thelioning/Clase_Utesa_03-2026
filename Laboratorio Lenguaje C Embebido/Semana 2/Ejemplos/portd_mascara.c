#include <avr/io.h>
#include <stdint.h>
int main(void)
{
    uint8_t patron = 5;
    patron |= (uint8_t)(1u << 3);
    DDRD = 0xFF;
    while (1) {
        PORTD = patron;
    }
}
