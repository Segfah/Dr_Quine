# README - Sully.asm

## Descripción del Programa

Este README tiene como objetivo explicar en detalle el funcionamiento del código ensamblador `Sully.asm`. Este programa es un **quine recursivo** que genera y ejecuta copias de sí mismo, decrementando un valor (`n`) hasta alcanzar `0`.

## Explicación del Código

```asm
%define n 6
```
Define el valor inicial de `n`, que controla cuántas versiones recursivas se crearán. El valor se reduce en cada iteración hasta llegar a `0`.

```asm
%define ASCII_ZERO 48
```
Define el valor ASCII para el carácter `'0'`, que se utilizará para formar los nombres de los archivos (`Sully_n.asm`).

### Sección `.text` - Código Ejecutable

```asm
section .text
default rel
global main
```
- **`section .text`**: Define la sección de código ejecutable.
- **`default rel`**: Permite el uso de direcciones relativas, lo que facilita la reubicación del código.
- **`global main`**: Declara `main` como el punto de entrada del programa.

```asm
main:
    push rbp
```
- **`main:`**: Marca el inicio de la función principal del programa.
- **`push rbp`**: Guarda el valor actual del registro base (`rbp`) para restaurarlo más adelante.

```asm
    mov rdi, FILENAME
    mov rsi, mode
    extern fopen
    call fopen
```
- **`mov rdi, FILENAME`**: Carga la dirección del nombre del archivo en `rdi`. Este nombre se define según el valor actual de `n`.
- **`mov rsi, mode`**: Carga el modo de apertura (`w`, para escritura) en `rsi`, que se utilizará con `fopen`.
- **`extern fopen`** y **`call fopen`**: Declaran y llaman a la función `fopen` para abrir un archivo en modo escritura. El descriptor del archivo se almacena en `rax`.

```asm
    mov rdi, rax
    mov rsi, code
```
- **`mov rdi, rax`**: Copia el descriptor del archivo (`rax`) en `rdi` para usarlo como argumento en `fprintf`.
- **`mov rsi, code`**: Carga la dirección de la cadena `code` en `rsi`, que contiene el contenido que se escribirá en el archivo.

```asm
    mov rdx, 10
    mov rcx, 34
    mov r8, n - 1
    mov r9, code
    xor rax, rax
```
- **`mov rdx, 10`**: Prepara el valor `10` (carácter de nueva línea) como argumento para `fprintf`.
- **`mov rcx, 34`**: Prepara el valor `34` (comillas dobles) como segundo argumento.
- **`mov r8, n - 1`**: Calcula `n - 1` y lo guarda en `r8` como tercer argumento para `fprintf`, representando la nueva versión de `n`.
- **`mov r9, code`**: Carga nuevamente la dirección de `code` en `r9`.
- **`xor rax, rax`**: Establece `rax` en `0` para cumplir con las convenciones de llamadas.

```asm
    extern fprintf
    call fprintf wrt ..plt
```
- **`extern fprintf`** y **`call fprintf wrt ..plt`**: Declaran y llaman a la función `fprintf` para escribir el contenido de `code` en el archivo, utilizando los argumentos preparados anteriormente.

#### Explicación de `call fprintf wrt ..plt`
- **`call fprintf wrt ..plt`** se utiliza para realizar una llamada a la función `fprintf` a través de la **Procedure Linkage Table (PLT)**.
  - **PLT (Procedure Linkage Table)**: La PLT es una estructura que se utiliza en los ejecutables y las bibliotecas compartidas para gestionar las llamadas a funciones externas. En este caso, `fprintf` está definido en una biblioteca compartida (`libc`), y el uso de la PLT permite que el enlazador resuelva la dirección de `fprintf` en tiempo de ejecución. 
  - **`wrt ..plt`**: Indica que la llamada debe ser hecha a través de la PLT, lo que facilita la resolución de la función `fprintf` en tiempo de ejecución, permitiendo el enlace dinámico y mejorando la eficiencia.

```asm
    extern fcloseall
    call fcloseall
```
- **`extern fcloseall`** y **`call fcloseall`**: Cierra todos los archivos abiertos para asegurar la liberación de recursos.

```asm
    mov rdi, cmd1
    extern system
    call system
```
- **`mov rdi, cmd1`**: Carga el comando de compilación (`cmd1`) en `rdi`. Este comando compila el archivo generado (`nasm` seguido de `gcc`).
- **`extern system`** y **`call system`**: Declara y llama a la función `system` para ejecutar el comando almacenado en `cmd1`.

```asm
    mov rdi, n - 1
    cmp rdi, 0
    jg _exe
```
- **`mov rdi, n - 1`**: Calcula `n - 1` y lo carga en `rdi`.
- **`cmp rdi, 0`**: Compara el valor de `rdi` con `0`.
- **`jg _exe`**: Si `rdi` es mayor que `0`, salta a la etiqueta `_exe` para ejecutar la siguiente versión del programa.

### Sección `.data` - Datos Utilizados

```asm
section .data
code: db "%%define n %3$d%1$c%%define ASCII_ZERO 48%1$c%1$csection .text ..."
```
- **`code`**: Contiene la plantilla del código fuente. Incluye especificadores (`%3$d`, `%1$c`, `%2$c`) que serán reemplazados para actualizar el valor de `n` y otros caracteres dinámicos en cada iteración.

```asm
FILENAME: db "Sully_", n - 1 + ASCII_ZERO, ".asm", 0
```
- **`FILENAME`**: Define el nombre del archivo que se generará, utilizando `n - 1 + ASCII_ZERO` para convertir el valor de `n` en un carácter ASCII adecuado.

```asm
cmd1: db "nasm -f elf64 Sully_", n - 1 + ASCII_ZERO, ".asm && gcc -Wall -Wextra -Werror -fPIE -pie -no-pie Sully_", n - 1 + ASCII_ZERO, ".o -o Sully_", n - 1 + ASCII_ZERO, " && echo -n", 0
```
- **`cmd1`**: Contiene el comando para ensamblar y compilar el archivo generado.

```asm
cmd2: db "./Sully_", n - 1 + ASCII_ZERO, 0
```
- **`cmd2`**: Contiene el comando para ejecutar el archivo generado (`./Sully_n`).

```asm
mode: db "w", 0
```
- **`mode`**: Define el modo de apertura del archivo como `w` (escritura).

### Etiquetas y Flujo del Programa

```asm
_exit:
    pop rbp
    ret
```
- **`_exit:`**: Marca el punto para limpiar el registro y finalizar la ejecución.
  - **`pop rbp`**: Restaura el valor del registro base (`rbp`).
  - **`ret`**: Retorna del procedimiento, finalizando la ejecución.

```asm
_exe:
    mov rdi, cmd2
    call system
    jmp _exit
```
- **`_exe:`**: Esta etiqueta se utiliza para ejecutar la siguiente versión del programa.
  - **`mov rdi, cmd2`**: Carga el comando para ejecutar el archivo generado.
  - **`call system`**: Llama a `system` para ejecutar el archivo.
  - **`jmp _exit`**: Salta a la etiqueta `_exit` para finalizar la ejecución.

## Explicación de los Especificadores de Formato

En la cadena `code`, se utilizan especificadores de formato que se reemplazan durante la ejecución del programa:

- **`%1$c`**: Se reemplaza por un salto de línea (`\n`).
- **`%2$c`**: Se reemplaza por comillas dobles (`"`).
- **`%3$d`**: Se reemplaza por el valor actual de `n - 1`, asegurando que cada versión del archivo contenga la actualización correcta de `n`.
