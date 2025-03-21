#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"
#include "utf8_check.h"
#include <string.h>
#include <ctype.h>

#define START_PRIME 101

void remove_whitespace(char* str) {
    int i = 0; j = 0;

    while (str[i]) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}

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

        // whitespaces!
        switch (line_count) {
            case 1:
            if (strcmp(buf, "P6")) {
                printf("spravne\n");
            }
            break;    
            
            case 2: {
            unsigned x;
            unsigned y;
            int scan;
            scan = scanf("%d %d", &x, &y);
            printf("%d %d %d\n", x, y, scan);
            break;
            }
            
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