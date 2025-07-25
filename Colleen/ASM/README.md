# README - Quine en Assembleur NASM (x86-64)

Ce README vise à expliquer en détail le fonctionnement du code assembleur.

## Sections du Code

Ce quine en NASM affiche son propre code source lors de l'exécution. Le code est principalement divisé en deux sections :

- **section .text** : Contient le code exécutable, y compris les fonctions définies telles que `main` et `empty`.
- **section .data** : Contient les données nécessaires, comme le texte du code lui-même, utilisé pour se répliquer.

## Comment fonctionne le quine ?

La section `.data` contient une chaîne avec le code source lui-même. La fonction principale (`main`) appelle `printf`, en passant cette chaîne et les arguments nécessaires pour imprimer correctement le code, y compris les sauts de ligne et les guillemets. Ainsi, le programme s'imprime lui-même.

### Section .text

1. `section .text`
   - Déclare la section de code exécutable. Cette section contient les instructions que le processeur exécutera.

2. `global main`
   - Déclare `main` comme un symbole global, permettant au linker de le trouver comme point d'entrée du programme.

3. `extern printf`
   - Informe l'assembleur de l'existence d'une fonction externe appelée `printf`, fournie par la bibliothèque standard C.

4. `; Ce commentaire est en dehors de la fonction main`
   - Un commentaire en dehors de la fonction `main`, requis par les spécifications du projet pour montrer la capacité à documenter le code.

5. `empty:`
   - Cette étiquette définit une fonction vide appelée `empty`. Son but est simplement d'être une fonction supplémentaire que `main` peut appeler.

6. `ret`
   - L'instruction `ret` est utilisée pour retourner de la procédure actuelle, rendant le contrôle à l'appelant.

### Fonction principale `main`

7. `main:`
   - Ici commence la définition de la fonction `main`, le point d'entrée du programme.

8. `push rbp`
   - Sauvegarde la valeur actuelle du registre de base de pile (`rbp`). Ceci fait partie du préambule standard pour maintenir l'intégrité du stack frame et faciliter le débogage.

     Le **stack frame** est une structure de données utilisée pour stocker les informations nécessaires à l'exécution des fonctions, y compris les paramètres, les variables locales et les adresses de retour. En sauvegardant la valeur de `rbp`, on peut restaurer l'état précédent de la pile, ce qui est essentiel pour le débogage et éviter les conflits entre fonctions.

9. `; Ce commentaire est à l'intérieur de la fonction main`
   - Ce commentaire est à l'intérieur de la fonction `main`, répondant aux exigences du projet d'inclure des commentaires dans le flux principal du code.

10. `call empty`
    - Appelle la fonction `empty`. Bien que cette fonction ne fasse rien, elle est présente pour répondre à l'exigence d'avoir une seconde fonction et pour illustrer l'utilisation de `call` en assembleur.

11. `lea rdi, [rel code]`
    - Charge l'adresse du label `code` dans le registre `rdi`. Ce registre est utilisé comme premier argument pour `printf`. `rel` indique que l'adresse est relative, ce qui est important pour la portabilité et la compatibilité avec l'adresse de base d'exécution.

     Selon la convention d'appel du système x86-64 sous Linux, les arguments d'une fonction sont passés via les registres dans l'ordre suivant : `rdi`, `rsi`, `rdx`, `rcx`, `r8`, et `r9`. `rdi` est utilisé comme premier argument car il fait partie de cette convention, permettant un appel efficace à des fonctions externes comme `printf`. Ainsi, l'adresse du bloc de données à imprimer est correctement passée comme premier argument.

12. `mov rsi, 10`
    - Place la valeur `10` dans le registre `rsi`. Cette valeur représente le caractère de nouvelle ligne (`\n`) dans la sortie et sera utilisée par `printf`.

13. `mov rdx, 96`
    - Place la valeur `96` dans le registre `rdx`. Ceci fait partie des arguments dont `printf` a besoin pour formater le contenu correctement.

14. `lea rcx, [rel code]`
    - Charge à nouveau l'adresse du texte de code dans `rcx`, qui peut être utilisé comme partie du format dans `printf`. Cette étape est nécessaire pour pouvoir imprimer tout le contenu correctement.

15. `call printf`
    - Appelle la fonction `printf` pour imprimer le contenu de `code`. Ici, `printf` utilisera les arguments précédents pour répliquer exactement le code du programme.

16. `pop rbp`
    - Restaure la valeur originale du registre de base de pile (`rbp`). Ceci est une partie essentielle de l'épilogue de la fonction pour nettoyer la pile avant de retourner.

17. `ret`
    - Termine la fonction `main` et rend le contrôle au système d'exploitation.

### Section .data

18. `section .data`
    - Déclare la section de données, qui contient des informations statiques utilisées par le programme. Dans ce cas, elle contient le texte du code lui-même pour qu'il puisse se répliquer.

19. `code db ...`
    - Ici, une constante appelée `code` est déclarée, utilisant `db` (define byte). `db` est utilisé pour stocker le texte du code source entre guillemets inversés. Les placeholders (`%1$c`, `%2$c`, `%3$s`) sont utilisés pour l'interpolation de chaînes lors de l'exécution, permettant au contenu d'être imprimé exactement comme écrit.
    - Le texte inclut le code complet du programme dans un format que `printf` peut interpréter pour se répliquer. Chaque ligne se termine par un code d'échappement approprié (`%1$c`, `%2$c`, `%3$s`), ce qui permet de répliquer le format du code original.
    - Enfin, `0x0` indique la fin de la chaîne, agissant comme un terminateur nul pour indiquer la fin de la donnée.


## Rappel :

Qu'est-ce qu'un Stack Frame ?

- Un stack frame est une structure créée à chaque appel de fonction, et détruite lorsque la fonction se termine. La structure du stack frame permet à chaque fonction d'avoir son propre contexte d'exécution sans interférer avec les autres fonctions. Voici comment le stack frame est structuré :
  - **Paramètres de la Fonction** : Lorsqu'une fonction est appelée, les paramètres sont stockés dans les registres s'il y a peu d'arguments ; s'il y en a plus que ce que les registres peuvent gérer, ils sont stockés dans la pile.
  - **Adresse de Retour** : Lors de l'appel d'une fonction, l'adresse à laquelle il faut revenir après l'exécution de la fonction est sauvegardée dans la pile. Ceci est fait automatiquement avec l'instruction `call`.
  - **Valeur précédente de RBP** : Le registre de base de pile (`rbp`) stocke l'adresse de base du stack frame actuel. Ce registre est sauvegardé dans la pile (`push rbp`) au début de la fonction, et restauré (`pop rbp`) à la fin de la fonction. En sauvegardant la valeur précédente de `rbp`, on peut maintenir la référence du stack frame précédent, ce qui est crucial pour restaurer l'état approprié à la fin de la fonction.
  - **Espace pour les Variables Locales** : Les variables locales sont stockées dans le stack frame de la fonction. Cela permet à chaque fonction d'avoir son propre ensemble de variables qui n'interfèrent pas avec les autres fonctions.
  - **Restauration du Stack Frame** : À la fin de la fonction, la valeur précédente de `rbp` est restaurée pour rendre la référence au stack frame précédent. Cela permet de maintenir une structure cohérente de la pile et facilite le débogage. Visuellement, le stack frame ressemble à ceci :
  ```
               ┌─────────────────────────┐
               │       Paramètres        │ ← Adresse la plus haute de la pile
               ├─────────────────────────┤
               │ Adresse de retour       │ ← Sauvegardée automatiquement avec `call`
               ├─────────────────────────┤
               │  Valeur précédente RBP  │ ← Sauvegardée avec `push rbp`
     RBP ────▶ │   (Base Pointer)        │
               ├─────────────────────────┤
               │    Variables locales    │ ← Espace réservé dans la pile
               │     de la fonction      │
               └─────────────────────────┘ ← Adresse la plus basse de la pile
  ```
  La création et la destruction des stack frames gèrent correctement les appels de fonctions et permettent la récursivité. Chaque fonction a son propre espace dans la pile, assurant qu'elle n'interfère pas avec les autres fonctions actives.

  Le stack frame est la "zone" de la pile réservée à une fonction spécifique, et la pile est le mécanisme qui permet à chaque fonction d'avoir son propre contexte et au programme d'appeler et de retourner des fonctions correctement.

- **Convention d'Appel** : Sur l'architecture x86-64, les six premiers arguments d'une fonction sont passés dans les registres `rdi`, `rsi`, `rdx`, `rcx`, `r8`, et `r9`, respectivement. Cette convention optimise la vitesse des appels de fonctions en évitant l'utilisation intensive de la pile, car accéder aux registres est plus rapide qu'accéder à la mémoire de la pile. Après ces six registres, tout argument supplémentaire est passé dans la pile.
