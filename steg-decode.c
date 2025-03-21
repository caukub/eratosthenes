#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"

#define START_PRIME 101

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Nesprávný počet argumentů. Program očekává pouze argument <soubor>");
        return 0;
    }

    FILE* ppm_file = fopen("du1-obrazek.ppm", "r");

    if (ppm_file == NULL) {
        error_exit("Soubor se nepodařilo přečíst");
        return 1;
    }

    int c;
    unsigned count = 0;

    while ((c = getc(ppm_file)) != EOF) {
        count++;

        if (c == '\0') {
            printf("jj\n");
        }

        if (count == 101) {
            printf("%d", c);
        }
    }

    printf("%d", count);

    fclose(ppm_file);
}