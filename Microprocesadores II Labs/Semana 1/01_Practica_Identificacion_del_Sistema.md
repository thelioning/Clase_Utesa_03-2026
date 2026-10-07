# Práctica 1: identificar el sistema y consultar sus documentos

UTESA · Taller de Microprocesadores II · Pareja de la teoría de semana 1

## Objetivos y materiales

Distinguir placa, microcontrolador, núcleo, memoria y periféricos. Materiales: Blue Pill sin alimentar, fotografía ampliada si es necesario, hoja de datos STM32F103x8/xB, RM0008, PM0056 y esquema de la placa incluidos en `Documentacion`. No se necesita programar ni alimentar el circuito.

## Procedimiento

1. Lea el marcado del chip y fotografíelo. Registre el texto observado; si no coincide con STM32F103C8T6, señale la diferencia sin asumir equivalencia.
2. Localice en la hoja de datos: núcleo, Flash del C8, SRAM, frecuencia máxima y alimentación. Complete una tabla con característica, valor, documento y apartado o página de la copia consultada.
3. Ubique en la placa: microcontrolador, regulador, conector USB, reset, BOOT0 y cabecera de depuración. Contraste con el esquema; anote diferencias visibles.
4. Para un controlador de riego, describa entradas, decisión, salida y circuito externo que accionaría una válvula. No conecte una válvula a un GPIO.
5. Calcule la memoria de 50 y de 100 muestras `uint16_t`, suponiendo dos bytes por elemento. Explique por qué el resultado no equivale a toda la RAM usada por el programa.
6. Escriba qué documento consultaría para encontrar la función de un pin, el registro de configuración GPIO y una limitación del silicio.

## Evidencias y evaluación

Entregue foto o dibujo identificado, tabla documental, cálculos y respuestas. Cada grupo de evidencias vale 2.5 puntos sobre 10. Se evalúa la correspondencia entre afirmación y documento, no memorizar páginas. Si no dispone de placa, marque la identificación como documental y no como observación física.

Resultado verificable: el estudiante puede señalar el chip y justificar sus características usando los documentos. Esta práctica no certifica que una placa sea original ni que funcione eléctricamente.
