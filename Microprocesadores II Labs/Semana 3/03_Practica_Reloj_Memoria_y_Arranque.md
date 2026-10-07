# Práctica de semana 3: observar reloj, memoria y arranque

UTESA · Taller de Microprocesadores II · STM32F103C8T6 / Blue Pill

## Objetivos, requisitos y alcance

Interpretar la configuración efectiva del reloj, localizar variables y seguir el inicio del programa. Requiere las prácticas de identificación y SWD, lectura de [la teoría de semana 3](../../Microprocesadores%20II%20Teoria/Semana%203/03_Reloj_Memoria_y_Arranque.md), Blue Pill revisada, ST-LINK, STM32CubeIDE y documentos del repositorio.

Se usa [Ejemplos/main.c](Ejemplos/main.c) en el proyecto mínimo de semana 2. El archivo no es un proyecto completo: deben conservarse startup, script de enlazado y configuración correcta del dispositivo. No se conectan cargas externas ni se modifican los registros RCC, FLASH o las opciones de arranque.

## Actividad 1. Preparar el proyecto

1. Copie el ejemplo en el proyecto STM32F103C8Tx; trabaje con una copia del proyecto anterior.
2. Seleccione compilación de depuración y optimización baja. Compile y conserve el log; identifique ELF y archivo `.map` del enlazador. Si no se genera `.map`, revise las opciones del enlazador del proyecto.
3. Lea el startup y localice `Reset_Handler`, la copia de `.data`, la inicialización de `.bss` y la llamada a `main`. Anote las llamadas adicionales y el orden que realmente aparece. No lo sustituya por un orden aprendido de memoria.
4. Mantenga el plan de conexión y alimentación revisado de semana 2. BOOT0 debe permanecer en 0; no cambie BOOT1 ni opciones de memoria.

Evidencia: dispositivo seleccionado, compilación y fragmento identificado del startup. No se pide modificar el archivo de inicio.

## Actividad 2. Observar la inicialización

Coloque un punto de interrupción en la primera sentencia de `main`, antes de capturar RCC_CR. Inicie una depuración que efectúe reset del sistema y se detenga en `main`.

En Expressions o la ventana equivalente, observe `con_valor`, `desde_cero`, `&con_valor` y `&desde_cero`. Prediga antes de observar: 5 y 0. Registre los valores y direcciones reales. Las direcciones no se fijan en el enunciado porque las asigna el enlazador.

Localice ambos símbolos en `.map`; anote su sección y dirección. Compruebe si caen dentro de `0x20000000` a `0x20004FFF`. Localice `.text` y la dirección de `main` en Flash. Si la optimización o el formato del mapa dificulta la consulta, registre la limitación y ajuste solo la configuración de depuración indicada.

Evidencia: tabla con símbolo, valor inicial, dirección, sección y captura. La dirección no debe confundirse con el contenido.

## Actividad 3. Leer la configuración de reloj

Avance hasta terminar las asignaciones de `latencia_flash`. El ejemplo toma instantáneas de RCC_CR, RCC_CFGR y FLASH_ACR y extrae campos. Ninguna sentencia escribe en esos registros.

Registre los tres valores completos en hexadecimal y estos campos decodificados:

| Variable del ejemplo | Campo leído | Valor observado |
|---|---|---|
| `fuente_sysclk` | RCC_CFGR.SWS | |
| `codigo_ahb` | HPRE | |
| `codigo_apb1` | PPRE1 | |
| `codigo_apb2` | PPRE2 | |
| `entrada_pll` | PLLSRC | |
| `division_hse_pll` | PLLXTPRE | |
| `codigo_pll` | PLLMUL | |
| `latencia_flash` | FLASH_ACR.LATENCY | |

Use las tablas de teoría o RM0008 para traducir **código a divisor**. Por ejemplo, PPRE1=4 significa /2, no /4. Use SWS para la fuente efectiva; una solicitud SW no demuestra por sí sola que haya terminado un cambio.

Si se selecciona HSI, use 8 MHz nominales y dígalo. Si se selecciona HSE o PLL derivada de HSE, compruebe la frecuencia externa en la documentación y placa concreta. Cuando no se pueda comprobar, conserve el cálculo simbólico y declare frecuencia desconocida.

Calcule SYSCLK, HCLK, PCLK1 y PCLK2; indique fuente, divisores y unidades. Compare APB1 con 36 MHz y APB2 con 72 MHz. Compare la latencia con la tabla aplicable de RM0008; si detecta una discrepancia, documéntela y solicite revisión del proyecto. No intente corregirla escribiendo registros en esta práctica.

Evidencia: instantáneas, tabla de campos y cálculo. Titule el resultado «frecuencia nominal inferida de la configuración». No lo presente como medición con osciloscopio.

## Actividad 4. Seguir cambios y efectuar reset

Avance una iteración del bucle: `con_valor` pasa de 5 a 6 y `desde_cero` de 0 a 1. Si reanuda libremente, pueden realizarse muchas iteraciones; no espere esos mismos valores después de un tiempo indeterminado.

Efectúe un reset completo mediante la herramienta y vuelva a detenerse antes de la primera sentencia de `main`. Compruebe que las variables vuelven a sus valores iniciales. Explique usando startup y secciones. No edite las variables desde Expressions para conseguir los resultados.

Si el reset del IDE no vuelve a ejecutar startup, registre el método usado y revise su configuración con el docente. Situar PC manualmente en `main` no prueba inicialización de `.data` y `.bss`.

Evidencia: valores antes/después de una iteración y tras reset, con explicación de por qué reset no es borrado físico de toda la SRAM.

## Actividad 5. Leer la tabla de vectores

Con el programa detenido, abra la vista de memoria en `0x08000000` y seleccione palabras de 32 bits. Lea las dos primeras entradas sin escribir en memoria. Contrástelas con la tabla del ELF y el símbolo `Reset_Handler`.

La primera entrada indica el valor inicial de MSP. En el script habitual del C8, el extremo superior de SRAM es `0x20005000`, una dirección justo después del último byte válido; es un punto inicial común para una pila que crece hacia direcciones menores, no otro byte de SRAM utilizable.

La segunda entrada contiene la dirección del manejador de reset con bit 0 a 1 para indicar Thumb. Para comparar la dirección del código use la entrada con bit 0 enmascarado, teniendo en cuenta cómo la herramienta presenta el símbolo. No pida que todas las direcciones de instrucciones observadas en PC sean impares.

Evidencia: dos entradas, interpretación y contraste con el proyecto. Si el firmware usa un bootloader o tabla reubicada, esta práctica necesita adaptación; no aplique sin comprobar el proyecto.

## Entrega y evaluación

Entregue proyecto o fuentes con configuración identificable, log, tabla de memoria, tabla de reloj, cálculos, evidencia de reset y vectores. Cada actividad vale 2 puntos: 1 por evidencia verificable y 1 por interpretación. Si no dispone de hardware, entregue la parte documental y los casos sintéticos de teoría como tales, dejando las observaciones físicas pendientes.

La práctica está completa cuando el estudiante puede justificar fuente efectiva, divisores, lugar de ejecución de las variables e inicio del firmware. No certifica la precisión real de un oscilador ni sustituye una prueba de cambio seguro del reloj.
