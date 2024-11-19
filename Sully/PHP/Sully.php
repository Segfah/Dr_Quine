<?php

$filename_template = "Sully_%d.php";
$n = 5;

if (preg_match("/Sully_(\d+)\.php$/", __FILE__, $matches)) {
    $n = (int)$matches[1];
    $n--;
}

if ($n < 0) {
    exit(0);
}

$filename = sprintf($filename_template, $n);
$code = '<?php

$filename_template = %7$cSully_%6$cd.php%7$c;
$n = %3$d;

if (preg_match("/Sully_(\d+)\.php$/", __FILE__, $matches)) {
    $n = (int)$matches[1];
    $n--;
}

if ($n < 0) {
    exit(0);
}

$filename = sprintf($filename_template, $n);
$code = %4$c%5$s%4$c;
file_put_contents($filename, sprintf($code, 10, 39, $n, 39, $code, 37, 34));

if ($n > 0) {
    system("php $filename");
}
';
file_put_contents($filename, sprintf($code, 10, 39, $n, 39, $code, 37, 34));

if ($n > 0) {
    system("php $filename");
}
