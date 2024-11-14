#include <stdio.h>

/* Este comentario está fuera de la función main */

void print_source();

int main() {
    /* Este comentario está dentro de la función main */
    print_source();
    return 0;
}

void print_source() {
    char *source = "#include <stdio.h>%1$c%1$c/* Este comentario está fuera de la función main */%1$c%1$cvoid print_source();%1$c%1$cint main() {%1$c    /* Este comentario está dentro de la función main */%1$c    print_source();%1$c    return 0;%1$c}%1$c%1$cvoid print_source() {%1$c    char *source = %3$c%4$s%3$c;%1$c    printf(source, 10, 34, 34, source);%1$c}%1$c";
    printf(source, 10, 34, 34, source);
}
