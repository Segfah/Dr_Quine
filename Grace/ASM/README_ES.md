# README - Grace.asm

## Descripción del Programa

Este README tiene como objetivo explicar en detalle el funcionamiento del código ensamblador.
Este quine en ensamblador genera un archivo `Grace_kid.asm` que contiene su propio código fuente. Utiliza macros para estructurar el flujo y llamadas al sistema para crear y escribir el archivo.

## Explicación del Código

```asm
section.text:
```
Define una sección de código en ensamblador que contiene la parte ejecutable del programa. La sección `.text` se usa para las instrucciones.

```asm
    global _start
```
Indica que la etiqueta `_start` será el punto de entrada del programa. Esta es la etiqueta que el enlazador buscará para iniciar la ejecución.

```asm
    extern dprintf
```
Informa al enlazador que el programa hace uso de la función `dprintf` definida externamente (generalmente en una biblioteca del sistema).

```asm
%define FILENAME `Grace_kid.asm`
```
Define una constante (`FILENAME`) que se usará para definir el nombre del archivo de salida. En este caso, `Grace_kid.asm` será el archivo que contiene el código fuente del programa.

```asm
%define init _start:
```
Define un macro llamado `init` que equivale a la etiqueta `_start:`. Es el punto donde inicia el código ejecutable.

```asm
%macro main 0
```
Define un macro llamado `main` que se utilizará como la parte principal del programa. La macro `main` no toma argumentos (de ahí el `0`).

### Dentro del Macro `main`

```asm
    lea rdi, [rel filename]
```
El macro `main` contiene la lógica principal: abre el archivo, escribe el código fuente usando `dprintf`, y termina el programa con una llamada a `syscall`.

## ¿Cómo funciona el quine?

El programa crea un archivo `Grace_kid.asm` y escribe en él una copia de su propio código fuente. Utiliza macros para estructurar el flujo y simplificar la autorreplicación.

Carga la dirección del nombre del archivo (`filename`) en el registro `rdi`, el cual se usa para pasar argumentos a las llamadas al sistema (`syscall`). Esto prepara el nombre del archivo para abrirlo o crearlo.

```asm
    mov rsi, 577
```
Este valor `01101` en **octal** (equivalente a `577` en **decimal**) representa las banderas que se pasarán a la llamada al sistema `open`. Estas banderas indican que se debe:
- **`O_WRONLY` (1)**: Abrir el archivo solo para escritura.
- **`O_CREAT` (64)**: Crear el archivo si no existe.
- **`O_TRUNC` (512)**: Truncar el archivo si ya existe, eliminando su contenido.

En octal, `01101` corresponde a la combinación de estos tres valores.

```asm
    mov rdx, 420
```
Define los **permisos** del archivo al crearlo. `0644` en octal se traduce a:
- **`rw-r--r--`**: Lectura y escritura para el propietario, y solo lectura para el grupo y otros.

```asm
    mov rax, 2
    syscall
```
Establece el número de la llamada al sistema (`syscall`) en `2` (que corresponde a la llamada `open`) y luego realiza la llamada al sistema para abrir o crear el archivo con el nombre, banderas y permisos especificados.

0 es read
1 es write
2 es open
3 es close
60 es exit
(man 2 syscalls)

```asm
    push rax
    pop rdi
```
El descriptor de archivo devuelto por la syscall `open` se encuentra ahora en `rax`. Este valor es movido a `rdi` para ser usado más adelante en la escritura del archivo.

    push rax coloca el valor del registro rax en la pila (stack).
    pop rdi toma el valor que está en la cima de la pila y lo pone en el registro rdi.

```asm
    lea rsi, [rel code]
```
Carga la dirección del código fuente (`code`) en el registro `rsi`, que es el segundo argumento para la llamada a `dprintf`.

```asm
    mov rdx, 10
    mov rcx, 37
    mov r8, 96
    mov r9, rsi
    call dprintf
```
Estos registros (`rdx`, `rcx`, `r8`, `r9`) se utilizan para preparar los argumentos adicionales que serán pasados a `dprintf`, que es una función que permite imprimir texto formateado en un archivo. En este caso, se utiliza para escribir el propio código del programa al archivo `Grace_kid.asm`.

```asm
    mov rax, 3
    syscall
```
Establece el valor de `rax` para realizar la syscall `close`, que cierra el archivo abierto.

```asm
    xor rdi, rdi
    mov rax, 60
    syscall
```
Configura los registros necesarios para realizar la syscall `exit`, cerrando el programa de manera correcta. `60` es el número de syscall correspondiente a `exit` y `xor rdi, rdi` establece el valor de salida (`0`, indicando que el programa terminó sin errores).

### Definición de la Cadena de Código Fuente

```asm
code db `section.text:%1$c	global _start%1$c	extern dprintf%1$c%1$c; Este programa genera un archivo Grace_kid.c que contiene su propio código...
```
Define la cadena de texto que contiene el código fuente del programa. Se utiliza para que el programa pueda escribir su propio código al archivo de salida.

```asm
filename db FILENAME, 0x0
```
Define el nombre del archivo (`Grace_kid.asm`) como una cadena terminada en `0x0`.

```asm
%endmacro
```
Indica el fin de la macro `main`.

```asm
init
    main
```
Llama al punto de entrada (`init`) y luego ejecuta el macro `main`, que realiza toda la operación descrita.
