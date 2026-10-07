# Práctica 2: preparar el entorno, conectar y verificar ejecución

UTESA · Taller de Microprocesadores II · Pareja de la teoría de semana 2

## Objetivo y requisitos

Crear y compilar un proyecto mínimo para STM32F103C8T6, identificar el dispositivo mediante SWD y comprobar una escritura en depuración. Requiere la identificación de semana 1, Blue Pill, ST-LINK compatible, cables, computadora con STM32CubeIDE y método de alimentación revisado. No se requiere conectar cargas externas.

## 1. Plan de conexión, sin alimentación

Prepare una tabla con señal, pin del programador y pin de la placa. Las señales son SWDIO → PA13, SWCLK → PA14, GND → GND y NRST si está disponible. Consulte el pin de referencia de tensión en el manual del programador. No asuma que alimenta la placa. Seleccione una fuente adecuada y dibuje cómo llega la alimentación al chip.

El docente revisará polaridad, nivel de 3.3 V de las señales, tierra común y ausencia de alimentación duplicada antes de conectar. Mantenga BOOT0 en 0 para arranque normal desde Flash.

## 2. Proyecto y compilación

Registre versión del IDE y chip seleccionado. Cree un proyecto para STM32F103C8Tx. Use la plantilla vacía cuando esté disponible; mantenga archivos de inicio y enlazador. Coloque en `main.c` el programa mínimo de la teoría o use `Ejemplos/main.c`. Compile y registre errores, advertencias y ruta del ELF. Corrija errores antes de conectar a depuración.

## 3. Identificación y ejecución

Conecte el ST-LINK y la alimentación revisada. Inicie depuración; registre la identificación que muestra la herramienta y cualquier mensaje. Si identifica un chip diferente, deténgase y contraste su documentación. No cambie protecciones, opciones de memoria ni efectúe un borrado masivo para resolver un fallo de conexión.

Coloque un punto de interrupción en la escritura `marcador = 1;`. Observe `marcador` antes y después de ejecutar esa línea; use compilación de depuración con optimización baja para facilitar la observación. Registre 0 antes de la primera escritura y 1 después. Al continuar, el programa repite esa escritura; no espere un LED ni una cuenta creciente.

## 4. Diagnóstico documentado

Si falla: compruebe chip seleccionado, alimentación, continuidad de GND, correspondencia SWDIO/SWCLK, cable, driver y configuración de conexión. Anote cada comprobación y su resultado. Una placa no identificada no debe presentarse como prueba satisfactoria.

## Entrega y evaluación

Tabla de conexiones y alimentación (3 puntos), proyecto compilable y registro de compilación (3), evidencia de identificación y de ejecución (3), explicación de limitaciones y fallos (1). Entregue `.c` y capturas. No publique números de serie del programador ni rutas personales que no sean necesarias.

La compilación local del ejemplo no valida alimentación, programación ni ejecución física; esas evidencias se obtienen en el laboratorio. Los registros GPIO se trabajarán en la semana correspondiente del plan.
