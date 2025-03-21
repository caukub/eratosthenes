#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"
#include "utf8_check.h"
#include <string.h>
#include <ctype.h>

#define START_PRIME 101

int check_first_line(const char* str) {
    // ^P6\s*
    if (str[0] != 'P' || str[1] != '6') {
        return -1;
    }

    for (unsigned i = 2; i < strlen(str); ++i) {
        if (!isspace(str[i])) {
            return -1;
        }
    }

    return 0;
}

int check_third_line(const char *str) {
    // 255
    if (str[0] != '2' || str[1] != '5' || str[2] != '5') {
        return -1;
    }


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
            if (check_p6_is_valid(buf)) {
                printf("ERROR");
            }
            break;    
            
            case 2:
            break;
            
            case 3:
            printf("3 >> %s", buf);
            if (strcmp(buf, "255\n") == 0) {
                printf("3: OK\n");
            } else {
                printf("3: ERROR\n");
            }
            break;
        }
    }

    if (line_count != 3) {
        printf("chyba");
    }

    fclose(ppm_file);
}