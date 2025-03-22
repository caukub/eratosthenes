#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "error.h"
#include "utf8_check.h"
#include <string.h>
#include <ctype.h>

#define START_PRIME 101

#include <stdbool.h>

int first_line_is_valid(const char* str) {
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

struct ImageData {
    unsigned xsize;
    unsigned ysize;
    bool is_valid;
};

struct ImageData get_image_data(const char *str) {
    // ^\d+\s*\d+\s*
    bool is_valid = true;

    // Image limit of 16 000
    char x_array[6] = {'\0', '\0', '\0', '\0', '\0', '\0', };
    char y_array[6] = {'\0', '\0', '\0', '\0', '\0', '\0', };

    if (!isdigit(str[0])) {
        is_valid = false;
    } else {
        x_array[0] = str[0];
    }

    bool whitespace_reached = false;
    unsigned char x_count = 1;
    unsigned char y_count = 0;

    bool only_whitespaces_left = false;

    for (unsigned i = 1; i < strlen(str); ++i) {
        if (only_whitespaces_left && !isspace(str[i])) {
            is_valid = false;
        }

        if (!whitespace_reached) {
            if (!isspace(str[i])) {
                if (str[i] == '0') {
                    x_array[x_count] = '0';
                } else {
                    x_array[x_count] = str[i];
                }
                x_count++;
            } else {
                whitespace_reached = true;
            }
        } else {
            if (!isspace(str[i])) {
                if (str[i] == '0') {
                    y_array[y_count] = '0';
                } else {
                    y_array[y_count] = str[i];
                }
                y_count++;
            } else {
                only_whitespaces_left = true;
            }
        }
    }

    if (x_count > 5 || y_count > 5 || !whitespace_reached) {
        is_valid = false;
    }

    // TODO: validace velikosti

    unsigned x;
    unsigned y;

    //x = atoi(x_array);
    //y = atoi(y_array);
    printf("\n");
    for (unsigned i = 0; i < 6; ++i) {
        if (x_array[i] == '\0') {
            printf(" 0x0 ");
        } else {
            printf(" %d ", x_array[i]);
        }
    }
    printf("\n");

    x = atoi(x_array);
    y = atoi(y_array);

    struct ImageData image_data;
    image_data.xsize = x;
    image_data.ysize = y;
    image_data.is_valid = is_valid;

    return image_data;
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
        line_count++;

        // whitespaces!
        switch (line_count) {
            case 1:
            if (first_line_is_valid(buf) != 0) {
                printf("1: ERROR");
            }
            break;
            case 2: {
            struct ImageData image_data = get_image_data(buf);
            
            printf(">> %d x %d\n", image_data.xsize, image_data.ysize);

            if (!image_data.is_valid) {
                printf("2: ERROR\n");
            }
            }
            break;
            
            case 3:
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