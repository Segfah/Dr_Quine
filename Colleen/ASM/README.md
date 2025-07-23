# README - Quine en Ensamblador NASM (x86-64)

Este README tiene como objetivo explicar en detalle el funcionamiento del código ensamblador.

## Secciones del Código

Este quine en NASM imprime su propio código fuente al ejecutarse. El código está dividido principalmente en dos secciones:

- **section .text**: Contiene el código ejecutable, incluyendo las funciones definidas, tales como `main` y `empty`.
- **section .data**: Contiene los datos necesarios, como el propio texto del código, utilizado para replicarse.

## ¿Cómo funciona el quine?

La sección `.data` contiene una cadena con el propio código fuente. La función principal (`main`) llama a `printf`, pasando esa cadena y los argumentos necesarios para imprimir correctamente el código, incluyendo los saltos de línea y comillas. Así, el programa se imprime a sí mismo.


### Sección .text

1. `section .text`

   - Declara la sección de código ejecutable. Esta sección contiene las instrucciones que el procesador ejecutará.

2. `global main`

   - Declara `main` como un símbolo global, permitiendo que el linker lo encuentre como el punto de entrada del programa.

3. `extern printf`

   - Informa al ensamblador de la existencia de una función externa llamada `printf`, proporcionada por la biblioteca estándar de C.

4. `; Este comentario está fuera de la función main`

   - Un comentario fuera de la función `main`, requerido como parte de las especificaciones del proyecto para mostrar la capacidad de documentar el código.

5. `empty:`

   - Esta etiqueta define una función vacía llamada `empty`. Su propósito es simplemente ser una función adicional que el `main` puede llamar.

6. `ret`

   - La instrucción `ret` se utiliza para retornar del procedimiento actual, devolviendo el control al llamador.

### Función principal `main`

7. `main:`

   - Aquí comienza la definición de la función `main`, el punto de entrada del programa.

8. `push rbp`

   - Guarda el valor actual del registro base de pila (`rbp`). Esto es parte del preámbulo estándar para mantener la integridad del stack frame y facilitar la depuración.

     El **stack frame** es una estructura de datos utilizada para almacenar la información necesaria para la ejecución de funciones, incluyendo parámetros, variables locales, y direcciones de retorno. Al guardar el valor de `rbp`, podemos restaurar el estado anterior del stack, lo cual es esencial para depurar el programa y evitar conflictos entre las funciones.

9. `; Este comentario está dentro de la función main`

   - Este comentario está dentro de la función `main`, cumpliendo con los requisitos del proyecto de incluir comentarios dentro del flujo principal del código.

10. `call empty`

    - Llama a la función `empty`. Aunque esta función no hace nada, está presente para cumplir con el requisito de tener una segunda función y para ilustrar el uso de `call` en ensamblador.

11. `lea rdi, [rel code]`

    - Carga la dirección de la etiqueta `code` en el registro `rdi`. Este registro se utiliza como el primer argumento para `printf`. `rel` indica que la dirección es relativa, lo cual es importante para mejorar la portabilidad y compatibilidad con la dirección base de ejecución.

     En la convención de llamadas del sistema x86-64 en Linux, los argumentos de una función se pasan a través de registros en el siguiente orden: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, y `r9`. `rdi` se utiliza como el primer argumento porque es parte de esta convención, lo cual permite una llamada eficiente a funciones externas como `printf`. De esta forma, la dirección del bloque de datos que queremos imprimir se pasa correctamente como el primer argumento.

12. `mov rsi, 10`

    - Coloca el valor `10` en el registro `rsi`. Este valor representa el carácter de nueva línea (`\n`) en la salida y será utilizado por `printf`.

13. `mov rdx, 96`

    - Coloca el valor `96` en el registro `rdx`. Esto es parte de los argumentos que `printf` necesita para formatear el contenido adecuadamente.

14. `lea rcx, [rel code]`

    - Carga nuevamente la dirección del texto de código en `rcx`, que puede ser utilizado como parte del formato en `printf`. Este paso es necesario para poder imprimir todo el contenido correctamente.

15. `call printf`

    - Llama a la función `printf` para imprimir el contenido del `code`. Aquí, `printf` utilizará los argumentos previos para replicar exactamente el código del programa.

16. `pop rbp`

    - Restaura el valor original del registro base de pila (`rbp`). Esta es una parte esencial del epílogo de la función para limpiar el stack antes de retornar.

17. `ret`

    - Termina la función `main` y devuelve el control al sistema operativo.

### Sección .data

18. `section .data`

    - Declara la sección de datos, que contiene información estática utilizada por el programa. En este caso, contiene el propio texto del código para que pueda replicarse.

19. `code db ...`

    - Aquí se declara una constante llamada `code`, utilizando `db` (define byte). `db` se utiliza para almacenar el texto del código fuente entre comillas invertidas. Los placeholders (`%1$c`, `%2$c`, `%3$s`) se utilizan para la interpolación de cadenas durante la ejecución, permitiendo que el contenido se imprima exactamente como está escrito.
    - El texto incluye el código completo del programa en un formato que `printf` puede interpretar para replicarse. Cada línea termina con un código de escape adecuado (`%1$c`, `%2$c`, `%3$s`), lo que permite replicar el formato del código original.
    - Finalmente, `0x0` indica el final de la cadena, actuando como un terminador nulo, para indicar el fin del dato.



## Recordatorio:


¿Qué es un Stack Frame?

- Un stack frame es una estructura que se crea cada vez que una función es llamada, y se destruye cuando dicha función termina. La estructura del stack frame permite a cada función tener su propio contexto de ejecución sin interferir con otras funciones. A continuación, se detalla cómo se estructura el stack frame:
  - **Parámetros de la Función**: Cuando se llama a una función, los parámetros que se le pasan se almacenan en registros si hay pocos argumentos; si hay más de los que los registros pueden manejar, se almacenan en la pila (stack).
  - **Dirección de Retorno**: Al invocar una función, la dirección a la cual se debe regresar después de completar la ejecución de la función se guarda en la pila. Esto se hace automáticamente con la instrucción `call`.
  - **Valor de RBP Anterior**: El registro base de pila (`rbp`) almacena la dirección base del stack frame actual. Este registro se guarda en la pila (`push rbp`) al inicio de la función, y se restaura (`pop rbp`) al final de la función. Al guardar el valor anterior de `rbp`, se puede mantener la referencia del stack frame anterior, lo cual es crucial para restaurar el estado adecuado cuando la función termine.
  - **Espacio para Variables Locales**: Las variables locales se almacenan dentro del stack frame de la función. Esto permite que cada función tenga su propio conjunto de variables que no interfieran con otras funciones.
  - **Restauración del Stack Frame**: Al finalizar la función, se restaura el valor anterior de `rbp` para devolver la referencia al stack frame anterior. Esto permite mantener una estructura coherente del stack y facilita la depuración. Visualmente, el stack frame se vería así:
  ```
               ┌─────────────────────────┐
               │       Parámetros        │ ← Dirección más alta del stack
               ├─────────────────────────┤
               │ Dirección de retorno    │ ← Guardada automáticamente con `call`
               ├─────────────────────────┤
               │  Valor anterior de RBP  │ ← Guardado con `push rbp`
     RBP ────▶ │   (Base Pointer)        │
               ├─────────────────────────┤
               │    Variables locales    │ ← Espacio reservado en la pila
               │     de la función       │
               └─────────────────────────┘ ← Dirección más baja del stack
  ```
  La creación y destrucción de los stack frames se encarga de gestionar adecuadamente las llamadas a funciones y permitir la recursividad. Cada función tiene su propio espacio en el stack, asegurando que no interfiera con otras funciones activas.



&#x20;

- **Convención de Llamadas**: En la arquitectura x86-64, los primeros seis argumentos de una función se pasan en los registros `rdi`, `rsi`, `rdx`, `rcx`, `r8`, y `r9`, respectivamente. Esta convención optimiza la velocidad de las llamadas a funciones al evitar el uso intensivo de la pila, ya que acceder a registros es más rápido que acceder a la memoria de la pila. Después de estos seis registros, cualquier argumento adicional se pasa en la pila.
