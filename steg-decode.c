// steg-decode.c
// Řešení IJC-DU1, příklad B, 24. 3. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "utf8-check.h"
#include "eratosthenes.h"

#define PRIME_START_INDEX 101
#define COLOR_COMPONENTS 3

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

#define BUFFER_SIZE 4096

void allocate(const char* file_name, unsigned xsize, unsigned ysize) {
   FILE *image_file = fopen(file_name, "r");

   if (image_file == NULL) {
     printf("Při otevírání souboru nastala chyba");
     return;
   }

   const unsigned bytes = (COLOR_COMPONENTS * xsize * ysize);

   unsigned char *ppm_data = malloc(bytes);

   if (ppm_data == NULL) {
     printf("Memory allocation failed\n");
     return;
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

   bitset_alloc(bitset, bytes);
   
   Eratosthenes(bitset);

   unsigned char_counter = 0;

   unsigned char byte = 0;
   unsigned bit_count = 0;

   unsigned char decoded_message[1024] = {0};
   
   for (unsigned idx = PRIME_START_INDEX; idx < bytes; ++idx) {
    if (bitset_getbit(bitset, idx)) {
        unsigned char color_value = ppm_data[idx+1];
        unsigned char lsb = color_value & 1;
        
        byte |= (lsb << bit_count);
        bit_count++;
        
        if (bit_count == CHAR_BIT) {
            if (byte == '\0') {
                break;
                }
                decoded_message[char_counter] = byte;
                byte = 0;
                bit_count = 0;
                
                char_counter++;
                
        }
    }
   }
    
    
    decoded_message[char_counter] = '\0';

    if (utf8_check(decoded_message) != NULL) {
        printf("UTF-8 is invalid!\n");
    }
    
   printf("%s", decoded_message);
   
   bitset_free(bitset);

   fclose(image_file);
   free(ppm_data);
}

// doladit checkovani validity
struct ImageData get_image_data(const char *str) {
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

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Nesprávný počet argumentů. Program očekává pouze argument <soubor>");
        return 0;
    }

    const char* file_name = argv[1];

    FILE* ppm_file = fopen(file_name, "r");

    if (ppm_file == NULL) {
        error_exit("Soubor se nepodařilo přečíst\n");
        return 1;
    }

    char buf[4096];
    unsigned line_count = 0;

    struct ImageData image_data;

    while (line_count != 3 && fgets(buf, sizeof(buf), ppm_file) != NULL) {
        line_count++;

        switch (line_count) {
            case 1:
            if (first_line_is_valid(buf) != 0) {
                error_exit("1: err\n");
            }
            break;
            case 2: {
            image_data = get_image_data(buf);

            if (!image_data.is_valid) {
                error_exit("2: err\n");
            }
            }
            break;
            
            case 3:
            if (third_line_is_valid(buf) != 0) {
                error_exit("3: err\n");
            }
            break;
        }
    }

    fclose(ppm_file);

    if (line_count < 3) {
        error_exit("(lines missing)");
        return 1;
    } else {
        allocate(file_name, image_data.xsize, image_data.ysize);
    }
}
