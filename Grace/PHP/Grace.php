<?php

define('FILE_GENERATED', 'Grace_kid.php');
define('CODE', '<?php%1$c%1$cdefine(%2$cFILE_GENERATED%2$c, %2$cGrace_kid.php%2$c);%1$cdefine(%2$cCODE%2$c, %2$c%3$s%2$c);%1$c$ft = function() {%1$c    $f = fopen(FILE_GENERATED, %2$cw%2$c);%1$c    if ($f) {%1$c        fprintf($f, CODE, 10, 39, CODE);%1$c        fclose($f);%1$c    }%1$c};%1$c%1$c/* Este programa genera un archivo Grace_kid.php que contiene su propio código */%1$c$ft();%1$c');
$ft = function() {
    $f = fopen(FILE_GENERATED, 'w');
    if ($f) {
        fprintf($f, CODE, 10, 39, CODE);
        fclose($f);
    }
};

/* Este programa genera un archivo Grace_kid.php que contiene su propio código */
$ft();
