# Semana 1: tipos de datos y variables

Versión de consulta: [01_Clase_Tipos_de_Datos_y_Variables.docx](01_Clase_Tipos_de_Datos_y_Variables.docx). Se adopta la versión anteriormente situada en la raíz: contiene la clase y una ampliación del montaje físico. La alternativa con reloj externo se conserva en `../Versiones_anteriores`.

La simulación de la clase usa **1 MHz**. Para el montaje físico, prevalece [Tarea_Practica_01_Montaje_Fisico_PORTD.docx](Tarea_Practica_01_Montaje_Fisico_PORTD.docx), que solicita cristal de 8 o 16 MHz y fusibles correspondientes. Son escenarios distintos. `F_CPU` informa al programa; no configura por sí sola el reloj ni los fusibles. El código actual sin retardos no necesita `F_CPU` para escribir el patrón estático.

No mezclar el montaje con cristal obligatorio de la tarea y el cristal opcional del anexo de la clase. El docente comprobará alimentación, reloj y fusibles antes de programar el equipo real.
