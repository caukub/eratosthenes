#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"
#include "utf8_check.h"

#define START_PRIME 101

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Nesprávný počet argumentů. Program očekává pouze argument <soubor>");
        return 0;
    }

    const char* file_name = argv[1];

    if (utf8_check(file_name) != NULL) {
        printf("CHYBA!\n");
    }

    FILE* ppm_file = fopen(file_name, "r");

    if (ppm_file == NULL) {
        error_exit("Soubor se nepodařilo přečíst\n");
        return 1;
    }

    unsigned char buf[4096];
    unsigned line_count = 0;

    while (line_count < 3 && fgets(buf, sizeof(buf), ppm_file) != NULL) {
        printf("%s", buf);
        line_count++;

        switch (line_count) {
            case 1:
            printf("t\n");
            break;    
            case 2:
            printf("u\n");
            break;
            case 3:
            printf("v\n");
            break;
        }
    }

    if (line_count != 3) {
        printf("chyba");
    }

    int c;
    unsigned count = 0;

    /*
    while ((c = getc(ppm_file)) != EOF) {
        count++;

        if (c == '\0') {
            //printf("jj\n");
        }

        if (count == 101) {
           // printf("%d", c);
        }
    }
    */

    fclose(ppm_file);
}