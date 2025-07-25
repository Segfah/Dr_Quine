# README - Grace.asm

## Description du Programme

Ce README vise à expliquer en détail le fonctionnement du code assembleur.
Ce quine en assembleur génère un fichier `Grace_kid.asm` qui contient son propre code source. Il utilise des macros pour structurer le flux et des appels système pour créer et écrire le fichier.

## Explication du Code

```asm
section.text:
```
Définit une section de code en assembleur qui contient la partie exécutable du programme. La section `.text` est utilisée pour les instructions.

```asm
    global _start
```
Indique que le label `_start` sera le point d'entrée du programme. C'est le label que le linker recherchera pour démarrer l'exécution.

```asm
    extern dprintf
```
Informe le linker que le programme utilise la fonction `dprintf` définie en externe (généralement dans une bibliothèque système).

```asm
%define FILENAME `Grace_kid.asm`
```
Définit une constante (`FILENAME`) qui sera utilisée pour définir le nom du fichier de sortie. Dans ce cas, `Grace_kid.asm` sera le fichier contenant le code source du programme.

```asm
%define init _start:
```
Définit une macro appelée `init` qui équivaut au label `_start:`. C'est le point où commence le code exécutable.

```asm
%macro main 0
```
Définit une macro appelée `main` qui sera utilisée comme la partie principale du programme. La macro `main` ne prend pas d'arguments (d'où le `0`).

### À l'intérieur de la Macro `main`

```asm
    lea rdi, [rel filename]
```
La macro `main` contient la logique principale : elle ouvre le fichier, écrit le code source en utilisant `dprintf`, et termine le programme avec un appel système.

## Comment fonctionne le quine ?

Le programme crée un fichier `Grace_kid.asm` et y écrit une copie de son propre code source. Il utilise des macros pour structurer le flux et simplifier l'autoréplication.

Il charge l'adresse du nom du fichier (`filename`) dans le registre `rdi`, qui est utilisé pour passer des arguments aux appels système (`syscall`). Cela prépare le nom du fichier pour l'ouverture ou la création.

```asm
    mov rsi, 577
```
Cette valeur `01101` en **octal** (équivalent à `577` en **décimal**) représente les flags qui seront passés à l'appel système `open`. Ces flags indiquent :
- **`O_WRONLY` (1)** : Ouvrir le fichier en écriture seule.
- **`O_CREAT` (64)** : Créer le fichier s'il n'existe pas.
- **`O_TRUNC` (512)** : Tronquer le fichier s'il existe déjà, supprimant son contenu.

En octal, `01101` correspond à la combinaison de ces trois valeurs.

```asm
    mov rdx, 420
```
Définit les **permissions** du fichier lors de sa création. `0644` en octal se traduit par :
- **`rw-r--r--`** : Lecture et écriture pour le propriétaire, et lecture seule pour le groupe et les autres.

```asm
    mov rax, 2
    syscall
```
Définit le numéro de l'appel système (`syscall`) à `2` (qui correspond à l'appel `open`) puis effectue l'appel système pour ouvrir ou créer le fichier avec le nom, les flags et les permissions spécifiés.

0 est read
1 est write
2 est open
3 est close
60 est exit
(man 2 syscalls)

```asm
    push rax
    pop rdi
```
Le descripteur de fichier retourné par la syscall `open` se trouve maintenant dans `rax`. Cette valeur est déplacée dans `rdi` pour être utilisée plus tard lors de l'écriture dans le fichier.

    push rax place la valeur du registre rax sur la pile (stack).
    pop rdi prend la valeur au sommet de la pile et la met dans le registre rdi.

```asm
    lea rsi, [rel code]
```
Charge l'adresse du code source (`code`) dans le registre `rsi`, qui est le second argument pour l'appel à `dprintf`.

```asm
    mov rdx, 10
    mov rcx, 37
    mov r8, 96
    mov r9, rsi
    call dprintf
```
Ces registres (`rdx`, `rcx`, `r8`, `r9`) sont utilisés pour préparer les arguments supplémentaires qui seront passés à `dprintf`, une fonction qui permet d'imprimer du texte formaté dans un fichier. Ici, elle est utilisée pour écrire le code du programme dans le fichier `Grace_kid.asm`.

```asm
    mov rax, 3
    syscall
```
Définit la valeur de `rax` pour effectuer la syscall `close`, qui ferme le fichier ouvert.

```asm
    xor rdi, rdi
    mov rax, 60
    syscall
```
Configure les registres nécessaires pour effectuer la syscall `exit`, fermant correctement le programme. `60` est le numéro de syscall correspondant à `exit` et `xor rdi, rdi` définit la valeur de sortie (`0`, indiquant que le programme s'est terminé sans erreur).

### Définition de la Chaîne de Code Source

```asm
code db `section.text:%1$c\tglobal _start%1$c\textern dprintf%1$c%1$c; Ce programme génère un fichier Grace_kid.c qui contient son propre code...`
```
Définit la chaîne de texte contenant le code source du programme. Elle est utilisée pour que le programme puisse écrire son propre code dans le fichier de sortie.

```asm
filename db FILENAME, 0x0
```
Définit le nom du fichier (`Grace_kid.asm`) comme une chaîne terminée par `0x0`.

```asm
%endmacro
```
Indique la fin de la macro `main`.

```asm
init
    main
```
Appelle le point d'entrée (`init`) puis exécute la macro `main`, qui réalise toute l'opération décrite.
