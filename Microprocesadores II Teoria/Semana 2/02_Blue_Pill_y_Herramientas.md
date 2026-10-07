# Semana 2: Blue Pill, documentos y herramientas

UTESA · Microprocesadores II · STM32F103C8T6

## Objetivos

Explicar el flujo fuente → compilación → firmware → programación → ejecución y preparar una conexión SWD. La práctica correspondiente está en `Microprocesadores II Labs/Semana 2`.

## Herramientas y productos del trabajo

STM32CubeIDE permite editar, compilar y depurar un proyecto. El compilador transforma C a código objeto; el enlazador combina objetos y organiza las secciones según el mapa de memoria. Un archivo ELF puede conservar símbolos para depuración; BIN y HEX representan contenido de programación. Cambiar la extensión de un archivo no convierte su formato.

Ejemplo: un error de sintaxis impide compilar; un símbolo no definido puede impedir enlazar; un firmware válido puede no ejecutarse si se seleccionó el chip equivocado, no se programó la Flash o la configuración de arranque no es la esperada.

## Conexión SWD

SWD usa SWDIO y SWCLK para depuración. Para el STM32F103C8T6, PA13 corresponde a SWDIO y PA14 a SWCLK. Se requiere referencia de tierra común. NRST puede facilitar conexión bajo reset. La función del pin de referencia de tensión del programador se verifica en su documentación: no se supone que todo pin rotulado 3.3 V pueda alimentar la placa.

Los clones ST-LINK V2 pueden tener conectores diferentes. Identifique señales por documentación y rotulado comprobado, no únicamente por posición física. Mantenga una sola fuente de alimentación prevista; no combine salidas de fuentes sin comprobar su funcionamiento.

## Alimentación y arranque

El microcontrolador opera con alimentación de 2.0 a 3.6 V; la placa puede admitir otra tensión en una entrada de regulador según su circuito. Que exista un pin «5V» en una placa no autoriza a aplicar 5 V a cualquier GPIO. En esta práctica se usan señales SWD a nivel de 3.3 V y se verifica el circuito de alimentación antes de conectarlo.

Para el arranque normal desde Flash, mantenga BOOT0 en 0. No se necesita cambiar opciones de protección de memoria ni fusibles para la identificación inicial.

## Uso del IDE sin perder el enfoque bare-metal

Seleccione exactamente STM32F103C8Tx al crear el proyecto. Para trabajar mediante registros, use un proyecto STM32 vacío si esa opción está disponible en la versión instalada. El proyecto conserva inicio, vector de interrupciones y enlazador; «sin HAL» no significa eliminar esos componentes. No agregue llamadas HAL para esta actividad.

Un programa mínimo puede ser:

```c
volatile unsigned marcador = 0;

int main(void)
{
    while (1) {
        marcador = 1;
    }
}
```

Este programa prueba compilación y ejecución en depuración, no activa un LED. `marcador` permanece en 1 después de la primera escritura; no es un contador. La variable global permite localizar el símbolo en depuración; se observa con el programa detenido.

## Preguntas

1. Distinga compilar, enlazar y programar.
2. Explique la necesidad de GND común en SWD.
3. Explique por qué el programa mínimo no enciende automáticamente un LED.
4. Distinga la alimentación del chip de la entrada del regulador de una placa.
5. Indique qué comprobar si el programador no identifica el dispositivo.

## Fuentes

Hoja de datos local STM32F103x8/xB: alimentación y tabla de pines. RM0008: mapa de memoria y configuración de arranque. Esquema Blue Pill local. Documentación del ST-LINK concreto para su pinout. El recorrido de menús puede variar con la versión del IDE; registrar la versión utilizada.
