# Índice temático - Laboratorio de C para sistemas embebidos

## Propósito

Construir una base sólida de programación en C y trasladarla de forma gradual a la programación bare-metal del ATmega328P. Se utilizará Microchip Studio para escribir y compilar, y Proteus para simular el archivo `.hex`. Cada tema seguirá la secuencia: explicación breve, ejemplos guiados, ejercicios en C y práctica verificable en simulación.

## Línea metodológica

1. Presentar el concepto y su relación con un registro o pin del microcontrolador.
2. Resolver un ejemplo corto en C, inicialmente sin hardware cuando sea conveniente.
3. Implementarlo en Microchip Studio, revisar errores y advertencias del compilador.
4. Cargar el archivo `.hex` en Proteus y comprobar el resultado con LEDs, pulsadores, terminal virtual u otros instrumentos.
5. Cerrar cada unidad con ejercicios graduados: reproducción, modificación y solución autónoma.

## Bloque I - Pensamiento computacional y fundamentos de C

### 1. Preparación del entorno y estructura mínima de un programa C

- Flujo de trabajo: escribir, compilar, corregir, generar archivo `.hex` y simular en Proteus.
- Estructura general de un programa en C: `main`, bloques, sentencias, comentarios y estilo.
- Qué es un sistema embebido y diferencia entre un programa de PC y firmware bare-metal.

### 2. Tipos de datos, constantes y variables

- Sistema decimal, binario y hexadecimal; por qué son importantes en microcontroladores.
- Tipos básicos: `char`, `int`, `long`, `float`, `double`, `void` y sus variantes `signed`/`unsigned`.
- Tamaño, rango y consumo de memoria de los tipos en el ATmega328P.
- Declaración, inicialización, asignación, constantes y `#define`.
- Identificadores, palabras reservadas y conversiones de tipo.

### 3. Operadores y expresiones

- Operadores aritméticos, relacionales, lógicos y de asignación.
- Incremento, decremento, precedencia y paréntesis.
- Operadores a nivel de bits: `&`, `|`, `^`, `~`, `<<` y `>>`.
- Corrimientos de bits a izquierda y derecha; relación con multiplicación, división y posición de un bit.
- Enmascaramiento de bits: preparar, activar, limpiar, alternar y consultar un bit.
- Ejercicios en Microchip Studio: construir máscaras y modificar un valor sin alterar los demás bits.

### 4. Entrada/salida de consola para aprender C

- Uso elemental de `printf` y `scanf` en programas de práctica para PC.
- Formatos básicos y depuración por mensajes.
- Límites de estas funciones en bare-metal: el hardware no ofrece consola por sí solo.

## Bloque II - Control del flujo y modularidad

### 5. Decisiones

- Expresiones booleanas.
- `if`, `if-else`, condiciones anidadas y operador ternario.
- `switch`, `case`, `default` y `break`.

### 6. Repetición

- Bucles `while`, `do-while` y `for`.
- Contadores, acumuladores y banderas.
- `break` y `continue`.
- Bucles bloqueantes: cuándo son útiles y por qué deben evitarse en muchas tareas embebidas.

### 7. Funciones y organización del programa

- Declaración, definición, prototipos, parámetros y retorno.
- Paso por valor y uso de punteros para modificar datos.
- Alcance y duración: variables locales, globales y `static`.
- Calificador `volatile`: cuándo una variable puede cambiar fuera del flujo normal del programa y por qué se usa con registros de hardware e interrupciones.
- Diferencia entre `const`, `static` y `volatile`.
- Ejercicios: contador actualizado en una interrupción y lectura segura desde el programa principal.
- Separación en archivos `.c` y `.h`; inclusión de cabeceras y guardas.
- Diseño de funciones pequeñas, reutilizables y comprobables.

## Bloque III - Estructuras de datos y memoria en C

### 8. Arreglos unidimensionales

- Declaración, inicialización, recorrido e índices.
- Límites del arreglo y prevención de accesos fuera de rango.
- Arreglos y funciones.
- Tablas de consulta: patrones de LED, códigos y conversiones.

### 9. Matrices y arreglos multidimensionales

- Matrices bidimensionales y su recorrido.
- Inicialización y paso a funciones.
- Aplicaciones: teclado matricial, tablas de caracteres y mapas de bits.

### 10. Caracteres y cadenas

- ASCII, `char`, terminador nulo y arreglos de caracteres.
- Lectura, copia, comparación y recorrido seguro de cadenas.
- Buffers fijos para UART y LCD.

### 11. Punteros, estructuras y memoria

- Dirección de memoria, desreferenciación y relación entre punteros y arreglos.
- Punteros a funciones (introducción).
- `struct`, `typedef`, enumeraciones y uniones.
- Representación compacta de datos y campos de bits (uso prudente).
- Memoria estática frente a dinámica; por qué normalmente se evita `malloc` en ATmega328P.

### 12. Calidad, depuración y buenas prácticas de C

- Errores de sintaxis, compilación, enlace y ejecución.
- Advertencias del compilador y conversiones peligrosas.
- Inicialización, nombres claros, comentarios útiles y formato.
- Pruebas por casos normales, límite y error.

## Bloque IV - Fundamentos de hardware y ATmega328P

### 13. Arquitectura mínima para bare-metal

- CPU, memoria Flash, SRAM, EEPROM, reloj, reset, registros y periféricos.
- Bits, bytes, registros de control y registro de estado.
- Datasheet: cómo localizar pines, registros, máscaras y secuencias de configuración.
- ATmega328P: puertos B, C y D; alimentación, reset, cristal y pinout.

### 14. Primera simulación: GPIO con registros

- Crear proyecto AVR GCC en Microchip Studio y seleccionar el ATmega328P.
- Colocar ATmega328P en Proteus, configurar reloj y cargar `.hex`.
- Ciclo editar-compilar-simular-observar-corregir.
- LED y resistencia: primera salida digital.

### 15. GPIO por registros

- Registros `DDRx`, `PORTx` y `PINx`.
- Configuración de entrada, salida, pull-up interno y estado flotante.
- Escritura y lectura de un pin con máscaras de bits.
- Prácticas: LED, pulsador, interruptor y secuencias de LEDs.

## Bloque V - Periféricos esenciales del ATmega328P

### 16. Tiempo y temporizadores

- Retardos por software y sus limitaciones.
- Prescaler, contador, comparación y desbordamiento.
- Timer0, Timer1 y Timer2: propósito y diferencias.
- Prácticas: parpadeo no bloqueante, temporización periódica y contador de eventos.

### 17. Interrupciones

- Sondeo frente a interrupciones.
- Vector de interrupción, ISR, variables `volatile` y secciones críticas.
- Interrupciones externas, cambio de pin y temporizadores.
- Prácticas: pulsador con interrupción y base de tiempo periódica.

### 18. PWM

- Ciclo de trabajo, frecuencia y aplicaciones.
- Modos PWM de los temporizadores y registros de comparación.
- Prácticas: brillo de LED y control básico de servomotor o motor simulado.

### 19. Conversión analógica-digital (ADC)

- Señal analógica, resolución, referencia y cuantización.
- Configuración y lectura del ADC.
- Prácticas: potenciómetro, sensor simulado y control de LED/PWM según medición.

### 20. Comunicación UART

- Comunicación serial asíncrona: baud rate, trama, TX y RX.
- Configuración del USART del ATmega328P.
- Transmisión y recepción por sondeo; introducción a recepción por interrupción.
- Prácticas: terminal virtual de Proteus, comandos simples y envío de mediciones.

### 21. Interfaces de uso frecuente

- I2C/TWI: concepto, direcciones y lectura/escritura básica.
- SPI: maestro, esclavo, reloj y transferencia.
- Aplicación según disponibilidad: LCD 16x2, sensor o memoria EEPROM externa.

## Bloque VI - Diseño bare-metal y proyecto integrador

### 22. Arquitectura de firmware

- Superloop cooperativo, máquina de estados y tareas periódicas.
- Separación entre drivers, lógica de aplicación y configuración.
- Archivos de configuración, macros y abstracción de pines.
- Evitar retardos largos; tratamiento básico de rebote de pulsadores.

### 23. Proyecto integrador en Proteus

- Especificación de requisitos y diagrama de bloques.
- Selección de entradas, salidas y periféricos.
- Implementación modular, simulación y plan de pruebas.
- Ejemplos: controlador de iluminación, estación de medición, contador programable o menú por UART/LCD.

## Orden de uso de los libros disponibles

1. **Fundamentos de programación: Piensa en C**: unidades 1 a 12, con énfasis en algoritmos, decisiones, ciclos, funciones, arreglos, matrices, cadenas y estructuras.
2. **Introducción al Lenguaje C**: refuerzo de sintaxis de C, ejercicios y consulta de punteros, memoria y bibliotecas.
3. A partir de la unidad 13 se complementará con el datasheet del ATmega328P y guías prácticas propias de Microchip Studio y Proteus, porque esos materiales son específicos de programación bare-metal.

## Resultado esperado

Al finalizar, el estudiante podrá resolver un problema, diseñar el algoritmo, implementarlo en C modular y controlar periféricos del ATmega328P directamente mediante registros, sin depender de Arduino ni de bibliotecas de alto nivel.
