# Práctica 2: calcular, comparar y modificar un byte

UTESA · Laboratorio de Lenguaje C Embebido

Antes de comenzar: leer `02_Operadores_y_Expresiones.md`. Las actividades 1–4 se ejecutan en un compilador C de PC. La actividad 5 usa el montaje de LEDs de semana 1 en Proteus. No se requiere diseñar una interrupción, una función propia ni un periférico nuevo.

## 1. División y resto

Declare `int componentes = 27` e `int capacidad = 8`. Calcule cajas completas y sobrantes. Muestre ambos resultados con `%d`. Repita con 32 componentes. Explique por qué obtener cajas completas no necesita una división real. Entregue una tabla con datos, predicción y salida.

## 2. Comparación y límites

Declare una lectura entera. Para 19, 20, 30 y 31, muestre los resultados de `lectura > 20`, `lectura >= 20`, `lectura <= 30` y `(lectura >= 20) && (lectura <= 30)`. Modifique el valor y ejecute de nuevo para cada caso. Explique por qué los valores 20 y 30 prueban los límites. No escriba comparaciones encadenadas.

## 3. Permiso y alarma

El equipo se habilita si hay permiso y no hay alarma. Escriba `permiso && !alarma`, con variables enteras 0 o 1. Pruebe las cuatro combinaciones, imprima el resultado y use `if` para mostrar «habilitado» o «bloqueado». Explique la diferencia entre `!alarma` y el complemento `~alarma`.

## 4. Incremento y agrupación

Con `int x = 4`, ejecute en sentencias independientes `int a = x++;` e `int b = ++x;`. Muestre `a`, `b` y `x`. Calcule también `2 + 3 * 4` y `(2 + 3) * 4`. Explique la diferencia sin combinar incrementos en una misma expresión.

## 5. PORTD sin alterar otros bits

Use ATmega328P y ocho ramas de LED con resistencia, tal como en semana 1. Configure `DDRD = 0xFF`. Empiece con `uint8_t patron = 5`. Realice cuatro compilaciones y simulaciones independientes: patrón inicial; activación del bit 3; limpieza del bit 2 sobre el resultado anterior; alternancia del bit 0 sobre el resultado anterior. No se necesita un retardo ni una secuencia automática.

En cada programa calcule el patrón antes del bucle y escriba `PORTD = patron` dentro del bucle. Use máscaras y operadores compuestos; no sustituya el cálculo por el decimal final. Registre decimal, binario, LEDs previstos y LEDs observados. Anote bit 0 como PD0. Para simulación use el reloj de 1 MHz de la clase vigente; el montaje físico conserva sus propias instrucciones de reloj y revisión docente.

## Entrega

Cinco programas o carpetas identificadas, tabla de cada actividad y explicación. Para la quinta agregue captura del circuito y ruta del `.hex` generado. El compilador no prueba por sí solo un montaje físico. Criterio: resultados coherentes, casos solicitados, máscaras que conservan los otros bits y explicación del procedimiento.
