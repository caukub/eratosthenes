// bitset.h
// Řešení DU1, příklad A + B, 24. 3. 2025
// Autor: caukub
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;

#include <limits.h>

#define BITS_PER_UL (sizeof(unsigned long) * CHAR_BIT)

#define bits_to_bitset_size(bits) ((bits % BITS_PER_UL == 0.0) ? (bits / BITS_PER_UL + 1) : (bits / BITS_PER_UL + 2))

#define bitset_size(name) ((unsigned long) name[0])

#define bitset_to_bitset_size(bitset) (bits_to_bitset_size(bitset_size(bitset)))

#define get_bitset_index_of_bit(bit) (bit / BITS_PER_UL + 1)
#define get_bitset_of_bit(bit) (bit % BITS_PER_UL)


#include <assert.h>
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

#define bitset_create(name, size) \
  static_assert(size > 0, "Velikost bitsetu musí být větší než 0"); \
  bitset_index_t name[bits_to_bitset_size(size)] = {0}; \
  name[0] = size;

#define bitset_alloc(name, size) \
  assert(size < 500000000); \
    \
  bitset_t name = calloc(bits_to_bitset_size(size), sizeof(bitset_index_t)); \
  if (name == NULL) { \
      printf("bitset_alloc: Chyba alokace paměti"); \
  } \
  name[0] = size;
 
#ifdef USE_INLINE

#include <stdbool.h>
inline void bitset_free(bitset_t bitset) {
  free(bitset);
}

inline void bitset_fill(bitset_t bitset, bool fill_ones) {
  for (unsigned idx = 1; idx < bitset_to_bitset_size(bitset); ++idx) {
    if (fill_ones) {
      bitset[idx] = ~0;
    } else {
      bitset[idx] = 0;
    }
  }
}

inline void bitset_setbit(bitset_t bitset, unsigned idx, bool set_one) {
  if (idx > bitset_size(bitset)) {
    error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)idx, (unsigned long)bitset_size(bitset));
  }

  unsigned long mask = set_one ? (1UL << get_bitset_of_bit(idx)) : ~(1UL << get_bitset_of_bit(idx));

  if (set_one) {
    bitset[get_bitset_index_of_bit(idx)] |= mask;
  } else {
    bitset[get_bitset_index_of_bit(idx)] &= mask;
  }
}

inline bitset_index_t bitset_getbit(bitset_t bitset, unsigned idx) {
  if (idx > bitset_size(bitset)) {
    error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)idx, (unsigned long)bitset_size(bitset));
  }
  return ((bitset[get_bitset_index_of_bit(idx)] >> get_bitset_of_bit(idx)) & 1);
}

#else

#define bitset_free(name) (free(name))

#define bitset_fill(name, fill_ones) do { \
  unsigned bitset_size = bitset_to_bitset_size(name); \
  for (unsigned idx = 1; idx < bitset_to_bitset_size(name); ++idx) { \
    if (fill_ones) { \
      name[idx] = ~0; \
    } else {  \
      name[idx] = 0; \
    } \
  } \
} while (0);

#define bitset_setbit(name, idx, set_one) do { \
  if (idx > bitset_size(name)) { \
    error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)idx, (unsigned long)bitset_size(name)); \
  } \
  bitset_index_t mask = set_one ? (1UL << get_bitset_of_bit(idx)) : ~(1UL << get_bitset_of_bit(idx)); \
    \
  if (set_one) { \
    name[get_bitset_index_of_bit(idx)] |= mask; \
  } else { \
    name[get_bitset_index_of_bit(idx)] &= mask; \
  } \
} while (0); \

#define bitset_getbit(name, idx) (idx > bitset_size(name) ? (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)idx, (unsigned long)bitset_size(name)),0) : ((name[get_bitset_index_of_bit(idx)] >> get_bitset_of_bit(idx)) & 1))

#endif
