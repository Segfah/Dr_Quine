#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME_TEMPLATE "Sully_%d.c"
#define EXEC_TEMPLATE "./Sully_%d"

int main() {
    int n = 5;

    if (strstr(__FILE__, "Sully_") != NULL) {
        sscanf(__FILE__, "Sully_%d.c", &n);
        n--;
    }

    if (n < 0) {
        return 0;
    }

    char filename[50];
    sprintf(filename, FILENAME_TEMPLATE, n);

    FILE *f = fopen(filename, "w");
    if (!f) {
        return 1;
    }

    char *code = "#include <stdio.h>%1$c#include <stdlib.h>%1$c#include <string.h>%1$c#include <fcntl.h>%1$c#include <unistd.h>%1$c%1$c#define FILENAME_TEMPLATE %2$cSully_%5$cd.c%2$c%1$c#define EXEC_TEMPLATE %2$c./Sully_%5$cd%2$c%1$c%1$cint main() {%1$c    int n = %3$d;%1$c%1$c    if (strstr(__FILE__, %2$cSully_%2$c) != NULL) {%1$c        sscanf(__FILE__, %2$cSully_%5$cd.c%2$c, &n);%1$c        n--;%1$c    }%1$c%1$c    if (n < 0) {%1$c        return 0;%1$c    }%1$c%1$c    char filename[50];%1$c    sprintf(filename, FILENAME_TEMPLATE, n);%1$c%1$c    FILE *f = fopen(filename, %2$cw%2$c);%1$c    if (!f) {%1$c        return 1;%1$c    }%1$c%1$c    char *code = %2$c%4$s%2$c;%1$c    fprintf(f, code, 10, 34, n, code, 37);%1$c    fclose(f);%1$c%1$c    char command[100];%1$c    sprintf(command, %2$cgcc -Wall -Wextra -Werror -o Sully_%5$c1$d Sully_%5$c1$d.c%2$c, n);%1$c    system(command);%1$c%1$c    if (n > 0) {%1$c        sprintf(command, EXEC_TEMPLATE, n);%1$c        system(command);%1$c    }%1$c%1$c    return 0;%1$c}%1$c";
    fprintf(f, code, 10, 34, n, code, 37);
    fclose(f);

    char command[100];
    sprintf(command, "gcc -Wall -Wextra -Werror -o Sully_%1$d Sully_%1$d.c", n); 
    system(command);

    if (n > 0) {
        sprintf(command, EXEC_TEMPLATE, n);
        system(command);
    }

    return 0;
}
