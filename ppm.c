// ppm.c
// Řešení IJC-DU1, příklad B, 24. 3. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "ppm.h"
#include "error.h"

#define BUFFER_SIZE 4096

int first_line_is_valid(const char* str) {
    // ^P6\s*
    if (!(str[0] == 'P' && str[1] == '6')) {
        return -1;
    }

    for (unsigned idx = 2; idx < strlen(str); ++idx) {
        if (!isspace(str[idx])) {
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

// doladit checkovani validity
struct ImageData get_image_resolution(const char *str) {
    // ^\d+\s*\d+\s*
    bool is_valid = true;

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
                x_array[x_count] = str[i];
                x_count++;
            } else {
                whitespace_reached = true;
            }
        } else {
            if (!isspace(str[i])) {
                y_array[y_count] = str[i];
                y_count++;
            } else {
                only_whitespaces_left = true;
            }
        }
    }

    unsigned x = atoi(x_array);;
    unsigned y = atoi(y_array);;

    if (x_count > 5 || y_count > 5 || !whitespace_reached || x > 16000 || y > 16000) {
        is_valid = false;
    }

    struct ImageData image_data = { .xsize = x, .ysize = y, .is_valid = is_valid };

    return image_data;
}

char *get_image_data(const char *file_name, unsigned xsize, unsigned ysize) {
    FILE *image_file = fopen(file_name, "r");

    if (image_file == NULL) {
        fclose(image_file);
        error_exit("Při otevírání souboru nastala chyba\n");
    }

    const unsigned bytes = (COLORS_IN_PIXEL * xsize * ysize);

    char* ppm_data = malloc(bytes);

    if (ppm_data == NULL) {
        free(ppm_data);
        error_exit("Memory allocation failed\n");
    }

    int c;
    unsigned count = 0;
    unsigned nl = 0;

    while ((c = fgetc(image_file)) != EOF) {
       if (c == '\n') {
           nl++;
       }

       if (nl > 2) {
        ppm_data[count] = c;
        count++;
       }
   }
   
   return ppm_data;
}

int third_line_is_valid(const char *str) {
    // 255
    if (!(str[0] == '2' && str[1] == '5' && str[2] == '5')) {
        return -1;        
    }

    for (unsigned idx = 3; idx < strlen(str); ++idx) {
        if (!isspace(str[idx])) {
            return -1;
        }
    }

    return 0;
}

struct ppm *ppm_read(const char* filename) {
    FILE *image_file = fopen(filename, "r");

    if (image_file == NULL) {
        fclose(image_file);
        error_exit("Při otevírání souboru nastala chyba");
    }

    struct ppm* ppm_struct;

    unsigned line_count = 0;
    char buf[BUFFER_SIZE];

    while (line_count != 3 && fgets(buf, sizeof(buf), image_file) != NULL) {
        line_count++;

        switch (line_count) {
            case 1:
            if (first_line_is_valid(buf) != 0) {
                fclose(image_file);
                error_exit("1: err\n");
            }
            break;
            case 2: {
            struct ImageData image_resolution = get_image_resolution(buf);

            ppm_struct->xsize = image_resolution.xsize;
            ppm_struct->ysize = image_resolution.ysize;

            if (!image_resolution.is_valid) {
                fclose(image_file);
                error_exit("2: image is too big or data is invalid\n");
            }
            }
            break;
            
            case 3:
            if (third_line_is_valid(buf) != 0) {
                fclose(image_file);
                error_exit("3: err\n");
            }
            break;
        }
    }

    if (line_count < 3) {
        fclose(image_file);
        error_exit("(lines missing)");
    } else {
        char* ppm_data = get_image_data(filename, ppm_struct->xsize, ppm_struct->ysize);
        ppm_struct->data = ppm_data;
    }

    fclose(image_file);

    return ppm_struct;
}

void ppm_free(struct ppm *p) {
    free(p);
}