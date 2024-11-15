#include <stdio.h>

#define FILE_GENERATED "Grace_kid.c"
#define CODE "#include <stdio.h>%1$c%1$c#define FILE_GENERATED %2$cGrace_kid.c%2$c%1$c#define CODE %2$c%3$s%2$c%1$c#define FT() int main() { FILE *f = fopen(FILE_GENERATED, %2$cw%2$c); if(f) { fprintf(f, CODE, 10, 34, CODE); fclose(f); } return 0; }%1$c%1$c/* Este programa genera un archivo Grace_kid.c que contiene su propio código */%1$cFT()%1$c"
#define FT() int main() { FILE *f = fopen(FILE_GENERATED, "w"); if(f) { fprintf(f, CODE, 10, 34, CODE); fclose(f); } return 0; }

/* Este programa genera un archivo Grace_kid.c que contiene su propio código */
FT()
