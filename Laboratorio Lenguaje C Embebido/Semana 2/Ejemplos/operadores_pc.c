#include <stdio.h>
#include <stdint.h>
int main(void)
{
    int componentes = 27;
    int capacidad = 8;
    int lectura = 30;
    int permiso = 1;
    int alarma = 0;
    int x = 4;
    int a = x++;
    int b = ++x;
    uint8_t patron = 5;
    printf("Cajas: %d; sobrantes: %d\n", componentes / capacidad, componentes % capacidad);
    printf("En intervalo: %d\n", (lectura >= 20) && (lectura <= 30));
    printf("Habilitado: %d\n", permiso && !alarma);
    printf("a=%d b=%d x=%d\n", a, b, x);
    patron |= (uint8_t)(1u << 3);
    printf("Activar bit 3: %u\n", (unsigned)patron);
    patron &= (uint8_t)~(1u << 2);
    printf("Limpiar bit 2: %u\n", (unsigned)patron);
    patron ^= (uint8_t)(1u << 0);
    printf("Alternar bit 0: %u\n", (unsigned)patron);
    return 0;
}
