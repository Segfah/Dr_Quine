# README - Sully.asm

## Description du Programme

Ce README vise à expliquer en détail le fonctionnement du code assembleur `Sully.asm`. Ce programme est un **quine récursif** qui génère et exécute des copies de lui-même, en décrémentant une valeur (`n`) jusqu'à atteindre `0`.

## Comment fonctionne le quine ?

Le programme contient une chaîne dans la section `.data` avec son propre code source. À chaque exécution, il décrémente la valeur de `n`, génère un nouveau fichier avec le code mis à jour, le compile et l'exécute. Ce processus se répète jusqu'à ce que `n` atteigne 0.

## Explication du Code

```asm
%define n 6
```
Définit la valeur initiale de `n`, qui contrôle combien de versions récursives seront créées. La valeur est réduite à chaque itération jusqu'à atteindre `0`.

```asm
%define ASCII_ZERO 48
```
Définit la valeur ASCII pour le caractère `'0'`, qui sera utilisé pour former les noms des fichiers (`Sully_n.asm`).

### Section `.text` - Code Exécutable

```asm
section .text
default rel
global main
```
- **`section .text`** : Définit la section de code exécutable.
- **`default rel`** : Permet l'utilisation d'adresses relatives, ce qui facilite la relocalisation du code.
- **`global main`** : Déclare `main` comme point d'entrée du programme.

```asm
main:
    push rbp
```
- **`main:`** : Marque le début de la fonction principale du programme.
- **`push rbp`** : Sauvegarde la valeur actuelle du registre de base (`rbp`) pour la restaurer plus tard.

```asm
    mov rdi, FILENAME
    mov rsi, mode
    extern fopen
    call fopen
```
- **`mov rdi, FILENAME`** : Charge l'adresse du nom du fichier dans `rdi`. Ce nom est défini selon la valeur actuelle de `n`.
- **`mov rsi, mode`** : Charge le mode d'ouverture (`w`, pour écriture) dans `rsi`, qui sera utilisé avec `fopen`.
- **`extern fopen`** et **`call fopen`** : Déclarent et appellent la fonction `fopen` pour ouvrir un fichier en mode écriture. Le descripteur du fichier est stocké dans `rax`.

```asm
    mov rdi, rax
    mov rsi, code
```
- **`mov rdi, rax`** : Copie le descripteur du fichier (`rax`) dans `rdi` pour l'utiliser comme argument dans `fprintf`.
- **`mov rsi, code`** : Charge l'adresse de la chaîne `code` dans `rsi`, qui contient le contenu à écrire dans le fichier.

```asm
    mov rdx, 10
    mov rcx, 34
    mov r8, n - 1
    mov r9, code
    xor rax, rax
```
- **`mov rdx, 10`** : Prépare la valeur `10` (caractère de nouvelle ligne) comme argument pour `fprintf`.
- **`mov rcx, 34`** : Prépare la valeur `34` (guillemet double) comme second argument.
- **`mov r8, n - 1`** : Calcule `n - 1` et le stocke dans `r8` comme troisième argument pour `fprintf`, représentant la nouvelle version de `n`.
- **`mov r9, code`** : Charge à nouveau l'adresse de `code` dans `r9`.
- **`xor rax, rax`** : Met `rax` à `0` pour respecter les conventions d'appel.

```asm
    extern fprintf
    call fprintf wrt ..plt
```
- **`extern fprintf`** et **`call fprintf wrt ..plt`** : Déclarent et appellent la fonction `fprintf` pour écrire le contenu de `code` dans le fichier, en utilisant les arguments préparés précédemment.

#### Explication de `call fprintf wrt ..plt`
- **`call fprintf wrt ..plt`** est utilisé pour effectuer un appel à la fonction `fprintf` via la **Procedure Linkage Table (PLT)**.
  - **PLT (Procedure Linkage Table)** : La PLT est une structure utilisée dans les exécutables et les bibliothèques partagées pour gérer les appels à des fonctions externes. Ici, `fprintf` est défini dans une bibliothèque partagée (`libc`), et l'utilisation de la PLT permet au linker de résoudre l'adresse de `fprintf` à l'exécution.
  - **`wrt ..plt`** : Indique que l'appel doit être fait via la PLT, ce qui facilite la résolution de la fonction `fprintf` à l'exécution, permettant le lien dynamique et améliorant l'efficacité.

```asm
    extern fcloseall
    call fcloseall
```
- **`extern fcloseall`** et **`call fcloseall`** : Ferme tous les fichiers ouverts pour assurer la libération des ressources.

```asm
    mov rdi, cmd1
    extern system
    call system
```
- **`mov rdi, cmd1`** : Charge la commande de compilation (`cmd1`) dans `rdi`. Cette commande compile le fichier généré (`nasm` suivi de `gcc`).
- **`extern system`** et **`call system`** : Déclare et appelle la fonction `system` pour exécuter la commande stockée dans `cmd1`.

```asm
    mov rdi, n - 1
    cmp rdi, 0
    jg _exe
```
- **`mov rdi, n - 1`** : Calcule `n - 1` et le charge dans `rdi`.
- **`cmp rdi, 0`** : Compare la valeur de `rdi` à `0`.
- **`jg _exe`** : Si `rdi` est supérieur à `0`, saute à l'étiquette `_exe` pour exécuter la prochaine version du programme.

### Section `.data` - Données Utilisées

```asm
section .data
code: db "%%define n %3$d%1$c%%define ASCII_ZERO 48%1$c%1$csection .text ..."
```
- **`code`** : Contient le modèle du code source. Inclut des spécificateurs (`%3$d`, `%1$c`, `%2$c`) qui seront remplacés pour mettre à jour la valeur de `n` et d'autres caractères dynamiques à chaque itération.

```asm
FILENAME: db "Sully_", n - 1 + ASCII_ZERO, ".asm", 0
```
- **`FILENAME`** : Définit le nom du fichier qui sera généré, en utilisant `n - 1 + ASCII_ZERO` pour convertir la valeur de `n` en un caractère ASCII approprié.

```asm
cmd1: db "nasm -f elf64 Sully_", n - 1 + ASCII_ZERO, ".asm && gcc -Wall -Wextra -Werror -fPIE -pie -no-pie Sully_", n - 1 + ASCII_ZERO, ".o -o Sully_", n - 1 + ASCII_ZERO, " && echo -n", 0
```
- **`cmd1`** : Contient la commande pour assembler et compiler le fichier généré.

```asm
cmd2: db "./Sully_", n - 1 + ASCII_ZERO, 0
```
- **`cmd2`** : Contient la commande pour exécuter le fichier généré (`./Sully_n`).

```asm
mode: db "w", 0
```
- **`mode`** : Définit le mode d'ouverture du fichier comme `w` (écriture).

### Étiquettes et Flux du Programme

```asm
_exit:
    pop rbp
    ret
```
- **`_exit:`** : Marque le point pour nettoyer le registre et terminer l'exécution.
  - **`pop rbp`** : Restaure la valeur du registre de base (`rbp`).
  - **`ret`** : Retourne de la procédure, terminant l'exécution.

```asm
_exe:
    mov rdi, cmd2
    call system
    jmp _exit
```
- **`_exe:`** : Cette étiquette est utilisée pour exécuter la prochaine version du programme.
  - **`mov rdi, cmd2`** : Charge la commande pour exécuter le fichier généré.
  - **`call system`** : Appelle `system` pour exécuter le fichier.
  - **`jmp _exit`** : Saute à l'étiquette `_exit` pour terminer l'exécution.

## Explication des Spécificateurs de Format

Dans la chaîne `code`, des spécificateurs de format sont utilisés et remplacés lors de l'exécution du programme :

- **`%1$c`** : Remplacé par un saut de ligne (`\n`).
- **`%2$c`** : Remplacé par des guillemets doubles (`"`).
- **`%3$d`** : Remplacé par la valeur actuelle de `n - 1`, garantissant que chaque version du fichier contient la mise à jour correcte de `n`.
