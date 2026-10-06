# Semana 1: sistemas embebidos y STM32

UTESA · Microprocesadores II · STM32F103C8T6

## Objetivo

Identificar entradas, procesamiento, salidas y firmware en un sistema embebido; distinguir microcontrolador, núcleo y placa. La práctica correspondiente está en `Microprocesadores II Labs/Semana 1`.

## Sistema embebido

Un sistema embebido combina hardware y software para cumplir una función dentro de un equipo. Un controlador de temperatura recibe una medición, compara con un valor configurado y acciona una salida. La función del programa depende de conexiones, tiempo de respuesta y límites eléctricos; compilar no demuestra que el equipo funcione.

Ejemplo: en un sistema de riego, un reloj y un horario son entradas de la decisión; el firmware determina si corresponde regar; un circuito de potencia acciona la válvula. El microcontrolador no alimenta directamente una válvula desde un GPIO.

## Microprocesador, microcontrolador y placa

El núcleo ejecuta instrucciones. El microcontrolador integra núcleo, memorias y periféricos. La placa conecta el microcontrolador con alimentación, componentes y pines accesibles. **Cortex-M3** es el núcleo; **STM32F103C8T6** es el microcontrolador; **Blue Pill** es una placa que suele montarlo. No son nombres equivalentes.

Un microprocesador normalmente necesita más recursos externos para formar el sistema; esta distinción no debe reducirse a «uno programa y el otro no».

## Qué incluye el STM32F103C8T6

Según la hoja de datos STM32F103x8/xB: núcleo de 32 bits, frecuencia máxima de 72 MHz, 64 KiB de Flash para el C8 y 20 KiB de SRAM. La Flash conserva el programa sin alimentación; la SRAM contiene datos de ejecución y pierde su contenido al retirar la alimentación. El tamaño de 32 bits del núcleo no obliga a que toda variable ocupe cuatro bytes.

La frecuencia máxima es un límite, no una medición del reloj de un proyecto. Una placa comercial puede tener un chip diferente o una identificación que debe comprobarse; no se presupone capacidad de Flash adicional a la especificada.

Ejemplo de memoria: un arreglo de 100 elementos `uint16_t` ocupa 200 bytes para sus elementos. Eso no incluye la pila, otras variables ni el código del programa.

## Firmware y acceso directo a registros

Firmware es el programa que se ejecuta en el equipo. En bare-metal se controlan periféricos mediante sus registros sin requerir un sistema operativo. La secuencia típica de una salida GPIO es habilitar el reloj del puerto, configurar el pin y escribir su estado. En esta semana se reconoce la secuencia; su programación corresponde a la unidad de GPIO.

Un registro es una posición de hardware con bits definidos por el fabricante. `volatile` obliga al compilador a tratar los accesos según las reglas del lenguaje; no configura el periférico y no garantiza atomicidad por sí solo.

## Documentación que responde cada pregunta

- Hoja de datos `stm32f103c8.pdf`: capacidad, pines, alimentación y límites eléctricos.
- RM0008: registros y secuencias de configuración de periféricos.
- PM0056: modelo de programación del núcleo Cortex-M3.
- Errata: limitaciones conocidas del silicio y condiciones de aplicación.
- Esquema Blue Pill: conexiones de la placa concreta, que deben contrastarse con la placa usada.

Los documentos están en `Microprocesadores II Labs/Documentacion`. Consultar un esquema de Blue Pill no sustituye leer la hoja de datos del chip.

## Comprobación de comprensión

1. Describa entradas, procesamiento y salidas de un contador con pulsador y display.
2. Distinga Flash y SRAM usando programa y contador como ejemplos.
3. Explique por qué una placa Blue Pill no es el núcleo Cortex-M3.
4. Calcule el espacio de 50 muestras `uint16_t`.
5. Explique por qué «máximo 72 MHz» no prueba que el equipo trabaje a 72 MHz.

## Fuentes

Hoja de datos STM32F103x8/xB: resumen, descripción y tabla de características; copias del fabricante incluidas en el repositorio. RM0008: capítulos de memoria, RCC y GPIO. PM0056: modelo del programador. Fuente oficial: https://www.st.com/resource/en/datasheet/stm32f103c8.pdf.
