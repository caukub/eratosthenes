// eratosthenes.c
// Řešení IJC-DU1, příklad A + B, 24. 3. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <math.h>
#include "bitset.h"
#include <stdbool.h>
#include "error.h"

void Eratosthenes(bitset_t bitset) {
    bitset_fill(bitset, true);
    bitset_setbit(bitset, 0, false);
    bitset_setbit(bitset, 1, false);

    unsigned long size = bitset_size(bitset);

    for (unsigned i = 2; i < sqrt(size); ++i) {
        for (unsigned j = i * i; j < size; j += i) {
            bitset_setbit(bitset, j, false);
        }
    }
}