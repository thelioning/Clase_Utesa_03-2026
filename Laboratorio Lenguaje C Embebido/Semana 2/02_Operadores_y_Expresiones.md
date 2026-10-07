# Clase 2: operadores y expresiones en C

UTESA · Laboratorio de Lenguaje C Embebido · ATmega328P

## Objetivos y punto de partida

El estudiante ya declara variables, reconoce un byte y representa valores con LEDs. Al terminar distinguirá asignación y comparación, resolverá expresiones y modificará bits sin alterar los restantes. Trabajará primero en consola; después aplicará una máscara a PORTD. Se introduce `if` solamente para comprobar condiciones; su desarrollo completo corresponde a la unidad de decisiones.

## Declaración, inicialización y asignación

La declaración presenta una variable y su tipo. La inicialización le da su primer valor al declararla; la asignación reemplaza posteriormente el valor. No lea una variable automática antes de inicializarla.

```c
int lectura = 5;  /* declaración con inicialización */
lectura = 8;      /* asignación: ahora contiene 8 */
```

`=` guarda un valor; `==` compara y produce 1 cuando hay igualdad o 0 cuando no la hay. `lectura ==` está incompleto: falta el segundo operando.

```c
int a = 5;
int iguales = (a == 5); /* iguales = 1; a sigue siendo 5 */
a = 2;                 /* a cambia a 2 */
```

`if (a = 5)` realiza una asignación y su condición resulta verdadera porque 5 es distinto de cero. Aunque puede compilar, no expresa la pregunta «¿a vale 5?». Para esa pregunta escriba `if (a == 5)`.

## Operadores aritméticos

`+`, `-`, `*` y `/` suman, restan, multiplican y dividen. `%` da el resto de una división entera. El divisor no puede ser cero. En estas actividades se usan valores pequeños para evitar desbordamientos.

```c
int total = 7 + 2;   /* 9 */
int diferencia = 7 - 2; /* 5 */
int producto = 7 * 2;   /* 14 */
int cociente = 7 / 2;   /* 3, división entre enteros */
int resto = 7 % 2;      /* 1 */
float resultado = 7 / 2;    /* 3.0: la división ocurrió antes */
float preciso = 7.0f / 2.0f; /* 3.5 */
```

Aplicación: con 27 componentes y cajas de 8, `27 / 8` produce 3 cajas completas y `27 % 8` deja 3 componentes.

## Incremento y decremento

`++` aumenta en uno y `--` disminuye en uno. La forma prefija modifica antes de producir el valor de la expresión; la posfija produce el valor anterior y después modifica la variable.

```c
int x = 4;
int antes = x++; /* antes = 4; x = 5 */
int despues = ++x; /* x = 6; despues = 6 */
x--; /* x = 5 */
```

Use sentencias separadas para aprenderlo. Evite modificar una variable varias veces en una misma expresión, por ejemplo `x++ + ++x`, que tiene comportamiento indefinido en C.

## Comparaciones

`>` y `<` significan mayor y menor; `>=` y `<=` incluyen igualdad. `!=` compara desigualdad. Todos producen un `int` de valor 0 o 1.

```c
int temperatura = 30;
int alta = (temperatura > 30);    /* 0 */
int limite = (temperatura >= 30); /* 1 */
int distinta = (temperatura != 25); /* 1 */
```

Para comprobar un intervalo escriba `(temperatura >= 20) && (temperatura <= 30)`. `20 <= temperatura <= 30` no tiene el significado matemático de un intervalo: C evalúa la primera comparación y compara su 0 o 1 con 30.

## Operadores lógicos

C considera falso el cero y verdadero cualquier valor distinto de cero. `&&` pide dos condiciones verdaderas; `||` pide al menos una; `!` invierte la verdad de una condición. `&&` y `||` evalúan de izquierda a derecha y omiten el segundo operando cuando ya conocen el resultado.

```c
int permiso = 1;
int alarma = 0;
int habilitado = permiso && !alarma; /* 1 */
int aviso = alarma || (permiso == 0); /* 0 */
```

`!` es negación lógica. `~` es complemento de bits; no son intercambiables.

## Operadores sobre bits

Cada posición se procesa por separado. Para una posición: `&` da 1 si ambos bits son 1; `|` si al menos uno es 1; `^` si son distintos. `~` invierte los bits del operando después de las promociones enteras.

```c
#include <stdint.h>
uint8_t a = 10; /* 00001010 */
uint8_t b = 12; /* 00001100 */
uint8_t ambos = (uint8_t)(a & b); /* 8: 00001000 */
uint8_t alguno = (uint8_t)(a | b); /* 14: 00001110 */
uint8_t diferentes = (uint8_t)(a ^ b); /* 6: 00000110 */
uint8_t invertido = (uint8_t)~a; /* 245: 11110101 */
```

Un `uint8_t` normalmente se promociona a `int` antes de `~`. La conversión final a `uint8_t` limita el resultado al byte; no suponga que `~a` por sí solo tiene tipo de ocho bits. `a && b` produce 1 para esos valores, mientras `a & b` produce 8.

## Corrimientos y máscaras

`<<` desplaza bits a la izquierda y `>>` a la derecha. Para estos ejemplos se usan enteros sin signo y cantidades de desplazamiento válidas. El desplazamiento debe ser menor que el número de bits del operando promocionado; nunca use una cantidad negativa. La equivalencia con multiplicar por potencias de dos requiere comprobar rango y tipo.

```c
uint8_t mascara = (uint8_t)(1u << 3); /* 8: bit 3 */
uint8_t mitad = (uint8_t)(12u >> 1);  /* 6 */
uint8_t patron = 5; /* 00000101 */
patron |= mascara; /* 13: activa bit 3 */
patron &= (uint8_t)~(1u << 2); /* 9: limpia bit 2 */
patron ^= (uint8_t)(1u << 0);  /* 8: alterna bit 0 */
int activo = (patron & mascara) != 0; /* 1 */
```

`a |= b` almacena el resultado de OR en `a`. Con variables simples equivale a `a = a | b`. También existen `+=`, `-=`, `*=`, `/=`, `%=` y otras asignaciones compuestas. Una operación de lectura-modificación-escritura de un registro no es automáticamente atómica; este ejemplo no usa interrupciones.

## Precedencia y paréntesis

Multiplicación, división y resto se agrupan antes que suma y resta. Los paréntesis expresan la agrupación deseada; la precedencia no define por sí sola el orden temporal de evaluación de todas las expresiones.

```c
int a = 2 + 3 * 4;   /* 14 */
int b = (2 + 3) * 4; /* 20 */
int c = (10 & 8) != 0; /* 1; paréntesis necesarios */
```

En `10 & 8 != 0`, la desigualdad se agrupa antes que `&`; por eso no es la prueba de máscara que se buscaba.

## `printf`, `%d` y una decisión sencilla

`printf` pertenece a `<stdio.h>`. `%d` representa un argumento de tipo `int`; no indica una variable ni realiza una asignación. En consola puede mostrar los resultados para comprobarlos. En firmware, una consola necesita una salida implementada, como UART; no aparece automáticamente en un pin.

```c
#include <stdio.h>
int main(void)
{
    int lectura = 30;
    printf("Lectura: %d\n", lectura);
    if (lectura >= 30) {
        printf("Limite alcanzado\n");
    } else {
        printf("Por debajo del limite\n");
    }
    return 0;
}
```

`if` ejecuta el primer bloque si la condición es distinta de cero; `else` ejecuta el segundo cuando es cero. Para mostrar `uint8_t` sin depender de su promoción, use `printf("%u\n", (unsigned)patron);`.

## Actividades y criterios

Realice las cinco actividades de `02_Practica_Operadores.md`. Entregue código, predicción anterior a la ejecución y resultados reales. Cada actividad vale 2 puntos: 1 por resultado comprobado y 1 por explicación. No presente una predicción como medición de hardware.

## Fuentes

Plan local: `../00_Indice_Temario_C_a_BareMetal.md`. Referencia de lenguaje: WG14, borrador público N1570 (C11), apartados 6.3.1.1, 6.5.3–6.5.16, 6.7.9, 6.8.4.1 y 7.21.6.1: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf. Hardware: hoja de datos ATmega328P incluida en la carpeta del curso, apartado de puertos de entrada/salida.
