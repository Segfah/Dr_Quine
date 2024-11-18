<?php

/* Este comentario está fuera de la función main */

function print_source() {
    /* Este comentario está dentro de la función main */
    $source = '<?php%1$c%1$c/* Este comentario está fuera de la función main */%1$c%1$cfunction print_source() {%1$c    /* Este comentario está dentro de la función main */%1$c    $source = %2$c%3$s%2$c;%1$c    printf($source, 10, 39, $source);%1$c}%1$c%1$cprint_source();%1$c';
    printf($source, 10, 39, $source);
}

print_source();
