#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"
#include "utf8_check.h"
#include <string.h>
#include <ctype.h>

#define START_PRIME 101

#include <stdbool.h>

struct ImageData {
    unsigned xsize,
    unsigned ysize,
    bool is_valid,
}

struct *ImageData first_line_is_valid(const char* str) {
    // ^P6\s*
    
    bool is_valid = true;
    unsigned x = 0;
    unsigned y = 0;

    if (str[0] != 'P' || str[1] != '6') {
        is_valid = false;
    }

    for (unsigned i = 2; i < strlen(str); ++i) {
        if (!isspace(str[i])) {
            return -1;
        }
    }

    return struct ImageData { .xsize = x, .ysize = y .is_valid = is_valid }
}

int second_line_is_valid(const char *str) {
    // ^\d+\s*\d+\s*
    if (!isdigit(str[0])) {
        return -1;
    }

    for (unsigned i = 1; i < strlen(str); ++i) {
        if (!isdigit(str[i] || !isspace(str[i]))) {
            return -1;
        }

        if (isspace(str[i])) {

        }
    }

    return 0;
}

int third_line_is_valid(const char *str) {
    // 255
    if (str[0] != '2' || str[1] != '5' || str[2] != '5') {
        return -1;
    }

    for (unsigned i = 3; i < strlen(str); ++i) {
        if (!isspace(str[i])) {
            return -1;
        }
    }

    return 0;
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
            if (first_line_is_valid(buf) != 0) {
                printf("1: ERROR");
            }
            break;    
            if (second_line_is_valid(buf) != 0) {
                printf("2: ERROR");
            }
            case 2:
            break;
            
            case 3:
            printf("3 >> %s", buf);
            if (third_line_is_valid(buf) != 0) {
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