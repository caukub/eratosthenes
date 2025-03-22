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

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    clock_t start = clock();
    bitset_create(p, 100);

    Eratosthenes(p);

    unsigned last_ten_primes[10] = {0};
    unsigned primes_count = 0;

    for (unsigned long i = 0; i < bitset_size(p); ++i) {
        if (bitset_getbit(p, i)) {
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

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}