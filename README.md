# Clase UTESA · Ciclo 03-2026

Mapa de materiales docentes. Actualización: 7 de octubre de 2026. «Disponible» significa que el archivo está publicado; no certifica todo el curso ni una prueba física de sus prácticas.

## Material publicado

| Asignatura | Material disponible | Cobertura pendiente |
|---|---|---|
| [Fundamentos de Física Eléctrica](Fundamento%20de%20Fisica%20Electrica) | Programa, documentos de evaluación, presentación base y semana 1 con presentación UTESA, guía y tarea | No hay semanas posteriores organizadas |
| [Laboratorio de C Embebido](Laboratorio%20Lenguaje%20C%20Embebido) | Índice de 23 temas; semana 1; clase, cinco actividades y ejemplos de operadores de semana 2; documentación AVR | Restantes temas del índice |
| [Microprocesadores II · Teoría](Microprocesadores%20II%20Teoria) | Plan de 12 semanas; clases desarrolladas de semanas 1–3 | Semanas 4–12 |
| [Microprocesadores II · Laboratorio](Microprocesadores%20II%20Labs) | 12 documentos técnicos; prácticas correspondientes a semanas 1–3; ejemplos C de depuración y lectura de registros | Prácticas de semanas 4–12 y pruebas físicas de las nuevas guías |
| [Introducción a la Ingeniería Electrónica](Introduccion%20a%20la%20Ingenieria%20Electronica) | Materiales PDF existentes de semanas 1 y 2 | Cuestionarios, siguientes semanas y selección de sus versiones |
| [Electrónica Analógica I](Electronica%20Analogica%20I) | Material de media onda y guía de siete prácticas, comunes para secciones 001 y 002 | Programa completo y siguientes unidades no documentados en este repositorio |

## Versiones de consulta

- Física, semana 1: `Clase_1_Campo_Electrico_UTESA.pptx`. Las otras presentaciones permanecen en `Versiones_anteriores`; UTESA y Actualizada tienen el mismo texto.
- C, semana 1: `Semana 1/01_Clase_Tipos_de_Datos_y_Variables.docx`, antes situado en la raíz. La alternativa de reloj externo se conserva en `Versiones_anteriores`.
- La clase de C usa simulación a 1 MHz; la tarea física independiente prescribe reloj externo de 8 o 16 MHz. Leer el README de semana 1 antes de combinarlas. `F_CPU` no cambia el reloj del chip.
- Los PDF de Introducción y de media onda se importaron sin cambiar su contenido. Los README de cada área identifican su alcance. No se publican solucionarios en este cambio.

## Planificación y próximos pasos

Los índices son planificación, no evidencia de clases impartidas. El índice de C prevé 23 temas; el de Microprocesadores vincula cada una de las 12 semanas de teoría a una práctica.

1. Realizar y registrar en laboratorio las nuevas prácticas de C y de identificación/SWD; documentar diferencias del equipo real.
2. Realizar la práctica de semana 3 de Microprocesadores (reloj, memoria y arranque) y desarrollar después semana 4 de GPIO con su práctica.
3. Preparar los siguientes temas de C según el índice, con atención a decisiones, consola y ejercicios graduales.
4. Revisar los cuestionarios de Introducción por separado antes de seleccionar versiones y recursos externos.
5. Contrastar Electrónica Analógica con su programa oficial antes de añadir unidades o declarar completa la asignatura.

## Recursos exclusivamente locales

Los libros completos se conservan fuera de GitHub y se excluyen de publicación: *Física Universitaria*, *Introducción al lenguaje C*, *Fundamentos de programación: Piensa en C*, *The Definitive Guide to the ARM Cortex-M3*, *Programming Embedded Systems, Second Edition* y *Electrónica: teoría de circuitos y dispositivos electrónicos*. Su ausencia en `main` es deliberada. Un nombre listado aquí no confirma que se pueda descargar desde el repositorio.

## Validación y límites

Los documentos nuevos se revisaron para coherencia de rutas y datos; el ejemplo de consola se compila y ejecuta como parte de la revisión. La compilación de ejemplos bare-metal se registrará según la disponibilidad de toolchains. No se afirma haber probado Blue Pill, ATmega328P, Proteus o ST-LINK físicamente. Consulte [el registro de cambios](CAMBIOS_2026-10-06.md) para resultados concretos, y [la actualización de semana 3](CAMBIOS_2026-10-07.md).
