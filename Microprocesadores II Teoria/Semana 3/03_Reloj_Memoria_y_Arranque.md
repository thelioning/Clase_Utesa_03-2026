# Semana 3: reloj, memoria y arranque del STM32

UTESA · Microprocesadores II · STM32F103C8T6 / Blue Pill

## Propósito y conocimientos previos

Explicar de dónde procede el reloj de ejecución, calcular sus divisiones, ubicar programa y variables, y seguir el inicio hasta `main`. Se presupone que el estudiante identifica la placa, consulta documentos y usa depuración SWD como en las semanas 1 y 2. La práctica asociada está en [Semana 3 del laboratorio](../../Microprocesadores%20II%20Labs/Semana%203/03_Practica_Reloj_Memoria_y_Arranque.md).

La sesión puede distribuirse en 25 minutos de reloj, 25 de memoria, 20 de arranque y 20 de ejercicios. El laboratorio tiene su propio procedimiento. Esta unidad observa la configuración existente; no implementa una conmutación del reloj.

## 1. Frecuencia y período

La frecuencia `f` indica ciclos por segundo; el período `T` es la duración de un ciclo. Para una señal periódica, `T = 1/f`. MHz significa millones de ciclos por segundo.

Ejemplo: a 8 MHz, `T = 1 / 8 000 000 = 125 ns`. A 72 MHz, `T ≈ 13.89 ns`. El período de reloj no es el tiempo de una instrucción C. Una instrucción C puede generar varias instrucciones del procesador; accesos a memoria, saltos y otros factores afectan su duración.

Un bucle de incrementos no constituye un reloj calibrado. Su velocidad depende del código generado y de la depuración, entre otros factores.

## 2. Fuentes del reloj: HSI, HSE y PLL

El HSI es el oscilador RC interno de alta velocidad, nominalmente de 8 MHz. Su frecuencia real tiene tolerancia. El HSE procede de un cristal o de una señal externa según el circuito y su configuración. Un cristal instalado no demuestra que sea la fuente seleccionada.

La PLL genera un reloj a partir de una entrada y un multiplicador. Para el STM32F103 de esta unidad, la entrada de la PLL puede proceder de `HSI/2` o de HSE, con la división correspondiente configurada. No traslade automáticamente este árbol a otros STM32.

Ejemplo de cálculo, sin modificar hardware: si HSE vale 8 MHz, entra sin división y el multiplicador es 9, `f_PLL = 8 × 9 = 72 MHz`. Si la entrada es HSI/2 y el multiplicador es 9, `f_PLL = (8/2) × 9 = 36 MHz` nominales. Son configuraciones distintas.

Después de un reset del sistema, HSI se selecciona como reloj del sistema. Antes de llegar a `main`, el código de inicio o las funciones que este llama pueden cambiar la configuración. Por eso se inspecciona el estado efectivo al entrar al programa.

## 3. SYSCLK, HCLK y relojes de los buses

SYSCLK es el reloj seleccionado para el sistema. El prescaler AHB produce HCLK; los prescalers APB1 y APB2 producen PCLK1 y PCLK2.

| Símbolo | Significado | Cálculo |
|---|---|---|
| `f_SYSCLK` | Frecuencia de la fuente seleccionada | Según HSI, HSE o PLL |
| `D_AHB` | Divisor del bus AHB | Decodificar HPRE |
| `f_HCLK` | Reloj AHB y del núcleo | `f_SYSCLK / D_AHB` |
| `D_APB1` | Divisor APB1 | Decodificar PPRE1 |
| `f_PCLK1` | Reloj APB1 | `f_HCLK / D_APB1` |
| `D_APB2` | Divisor APB2 | Decodificar PPRE2 |
| `f_PCLK2` | Reloj APB2 | `f_HCLK / D_APB2` |

Para STM32F103, APB1 admite hasta 36 MHz; APB2, hasta 72 MHz. Con SYSCLK=72 MHz, AHB dividido por 1, APB1 por 2 y APB2 por 1, se obtienen HCLK=72 MHz, PCLK1=36 MHz y PCLK2=72 MHz.

Estos relojes no equivalen necesariamente al reloj interno de cada periférico. En particular, ciertos temporizadores aplican una regla adicional cuando el prescaler APB no vale 1; se estudiará en la unidad de temporizadores. Tampoco la opción de velocidad GPIO «2 MHz» selecciona la frecuencia de la CPU.

## 4. Interpretar RCC_CFGR sin escribirlo

La base RCC es `0x40021000`; RCC_CFGR está en base + `0x04`. `SW` indica la selección solicitada y `SWS` el estado efectivo de la fuente. Para saber qué se está usando se lee **SWS**.

| Campo | Bits | Interpretación |
|---|---|---|
| SWS | 3:2 | 0: HSI; 1: HSE; 2: PLL; 3: no aplicable |
| HPRE | 7:4 | 0–7: /1; 8: /2; 9: /4; 10: /8; 11: /16; 12: /64; 13: /128; 14: /256; 15: /512 |
| PPRE1 | 10:8 | 0–3: /1; 4: /2; 5: /4; 6: /8; 7: /16 |
| PPRE2 | 13:11 | Misma codificación que PPRE1 |
| PLLSRC | 16 | 0: HSI/2; 1: HSE |
| PLLXTPRE | 17 | Para entrada HSE de PLL: 0: /1; 1: /2 |
| PLLMUL | 21:18 | 0–13: multiplicador = código + 2; 14 y 15: ×16 |

Ejemplo: `fuente = (cfgr >> 2) & 3u;`. Desplazar alinea el campo con los bits inferiores; la máscara conserva sus dos bits. Con `cfgr = 0x001D040A`, se obtiene SWS=2, HPRE=0, PPRE1=4, PPRE2=0, PLLSRC=1, PLLXTPRE=0 y PLLMUL=7. Si HSE se ha confirmado como 8 MHz, el cálculo produce 72/72/36/72 MHz para SYSCLK/HCLK/PCLK1/PCLK2. El hexadecimal es un ejemplo didáctico, no una medición de la placa del estudiante.

Si SWS selecciona HSE o PLL derivada de HSE y no se conoce la frecuencia externa, no se puede obtener un resultado numérico justificado. Consulte la placa y su documentación antes de suponer 8 MHz.

## 5. Memoria del C8: direcciones y capacidad

Para el STM32F103C8 especificado: 64 KiB de Flash y 20 KiB de SRAM. KiB equivale a 1024 bytes. El mapa siguiente corresponde al chip, no a cualquier placa comercial con el mismo aspecto.

| Región | Dirección inicial | Último byte para esta capacidad | Uso típico |
|---|---|---|---|
| Flash principal | `0x08000000` | `0x0800FFFF` | Programa y datos que se conservan sin energía |
| SRAM | `0x20000000` | `0x20004FFF` | Variables de ejecución y pila |

La dirección es la ubicación; el contenido es el valor almacenado. El espacio de direcciones de 32 bits no implica tener 4 GiB de memoria física.

Ejemplo: `uint32_t dato = 5;` puede tener dirección de ejecución en SRAM y valor inicial almacenado en Flash. Son ubicaciones con funciones distintas, no necesariamente dos variables independientes.

## 6. Secciones del programa

En un proyecto enlazado convencional para ejecución desde Flash:

- `.text` contiene código; `.rodata` suele contener constantes.
- `.data` contiene variables estáticas con valor inicial distinto de cero. Su imagen inicial suele estar en Flash y su dirección de ejecución en SRAM.
- `.bss` reserva espacio para variables estáticas que deben comenzar en cero. No necesita almacenar en Flash una copia completa de todos esos ceros.
- La pila usa SRAM para llamadas, retornos y datos automáticos según el código generado.

La ubicación real se comprueba en el script de enlazado y el archivo `.map`. `const` por sí solo no demuestra que todo objeto termine en Flash: influyen duración, uso, optimización y enlazado. Para esta práctica se siguen dos variables globales `volatile`, sin introducir asignación dinámica de memoria.

Ejemplo: `volatile uint32_t con_valor = 5;` se espera en `.data`; `volatile uint32_t desde_cero;`, en `.bss`, con un toolchain y script convencionales. Al entrar en `main`, sus valores son 5 y 0 porque el código de inicio preparó las secciones, no porque `main` ya haya ejecutado esas declaraciones como sentencias.

## 7. Qué ocurre antes de main

Con BOOT0=0, el arranque selecciona la Flash principal. El espacio de arranque en `0x00000000` permite acceder a la memoria seleccionada mediante un alias; la Flash sigue accesible en `0x08000000`.

En el reset, el núcleo obtiene el valor inicial del puntero principal de pila de la primera entrada de la tabla de vectores y la dirección de ejecución del manejador de reset de la segunda. El proyecto normalmente define un `Reset_Handler` que prepara el entorno de C y termina llamando a `main`.

Para comprobar el proceso, se lee el archivo de inicio del proyecto: copia de `.data`, puesta a cero de `.bss`, llamadas de inicialización y entrada en `main`. La posición exacta de `SystemInit` respecto de esas acciones depende del archivo suministrado por el proyecto; no se presume un orden sin leerlo. También puede haber inicialización de la biblioteca C.

Resetear no significa borrar físicamente toda la SRAM ni borrar la Flash. Que las variables globales vuelvan a 5 y 0 al llegar a `main` se explica por el reinicio del entorno de C. Un reinicio de depuración que solo cambia PC no equivale a un reset completo del chip.

## 8. Latencia de Flash y límites del cálculo

RM0008 establece, para el STM32F103 tratado, 0 estados de espera hasta 24 MHz, 1 por encima de 24 y hasta 48 MHz, y 2 por encima de 48 y hasta 72 MHz según su tabla de latencia. FLASH_ACR está en `0x40022000`; LATENCY ocupa bits 2:0.

Aumentar la frecuencia requiere revisar alimentación, latencia, prescalers y secuencia de cambio del fabricante. Esta práctica solamente lee FLASH_ACR; no cambia la PLL ni la latencia. Una tabla de cálculo no es un procedimiento suficiente para reconfigurar el reloj.

## 9. Ejercicios para resolver antes del laboratorio

1. Calcule el período de HCLK a 8 y 36 MHz, con unidades.
2. Con HSI/2 y multiplicador 9, AHB /1, APB1 /2 y APB2 /1, calcule los cuatro relojes.
3. Interprete `RCC_CFGR = 0x00000000` en términos de fuente y divisores. Indique qué supuesto nominal usa al dar MHz.
4. Interprete `0x001D040A` suponiendo HSE confirmado de 8 MHz. Explique por qué PCLK1 no es 72 MHz.
5. Explique por qué una variable de `.data` tiene dirección de ejecución en SRAM y valor inicial conservado en Flash.
6. Explique qué evidencia distinguiría un reset completo de volver manualmente al inicio de `main`.

## Fuentes y alcance

Referencia principal: [RM0008 del repositorio](../../Microprocesadores%20II%20Labs/Documentacion/01_STM32F103/RM0008-STM32F103XX.pdf), Rev 21: arquitectura y mapa de memoria, configuración de arranque, reloj RCC para dispositivos de baja/media/alta/XL densidad, RCC_CR, RCC_CFGR y FLASH_ACR. Complemento: [PM0056](../../Microprocesadores%20II%20Labs/Documentacion/01_STM32F103/PM0056%20Programing%20manual.pdf), modelo del programador y tabla de vectores; [hoja de datos STM32F103x8/xB](../../Microprocesadores%20II%20Labs/Documentacion/01_STM32F103/stm32f103c8.pdf), capacidades y límites. No usar los capítulos de connectivity line como sustitución de RCC del F103.
