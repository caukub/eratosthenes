// steg-decode.c
// Řešení DU1, příklad B, 24. 3. 2025
// Autor: caukub
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "ppm.h"
#include "eratosthenes.h"
#include "error.h"
#include "utf8-check.h"

#define PRIMES_START_INDEX 101

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Nesprávný počet argumentů. Program očekává jediný argument <soubor>");
        return 0;
    }

    const char* file_name = argv[1];
    struct ppm* ppm_struct = ppm_read(file_name);

    unsigned bytes = (COLORS_IN_PIXEL * ppm_struct->xsize * ppm_struct->ysize);

    bitset_alloc(bitset, bytes);
   
    Eratosthenes(bitset);

    unsigned char_counter = 0;

    unsigned char byte = 0;
    unsigned bit_count = 0;

    unsigned char decoded_message[1024] = {0};

    char* ppm_data = ppm_struct->data;
   
    for (unsigned idx = PRIMES_START_INDEX; idx < bytes; ++idx) {
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
   
   //bitset_free(bitset);
}
