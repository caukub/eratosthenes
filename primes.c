// primes.c
// Řešení DU1, příklad A, 24. 3. 2025
// Autor: caukub
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "eratosthenes.h"

void print_last_ten_primes(bitset_t bitset) {
    unsigned last_ten_primes[10] = {0};
    unsigned primes_count = 0;

    for (unsigned long i = 0; i < bitset_size(bitset); ++i) {
        if (bitset_getbit(bitset, i)) {
            if (primes_count >= 10) {
            for (unsigned j = 0; j < 9; ++j) {
                last_ten_primes[j] = last_ten_primes[j + 1];
            }
            last_ten_primes[9] = i;
        } else {
            last_ten_primes[primes_count] = i;
            primes_count++;
          }
        }
    }

    for (unsigned i = 0; i < 10; ++i) {
        if (last_ten_primes[i] != 0) {
            printf("%d\n", last_ten_primes[i]);
        }    
    }
}

int main(void) {
    clock_t start = clock();
    bitset_create(p, 333000001);

    Eratosthenes(p);

    print_last_ten_primes(p);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
