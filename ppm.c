#include "ppm.h"

#include <stdio.h>
#include <stdlib.h>

struct ppm *ppm_read(const char *filename) {
  FILE *ppm_file = fopen("du1-obrazek.ppm", "r");

  if (ppm_file == NULL) {
    // err
  }

  return NULL;
}

void ppm_free(struct ppm *p) {
    free(p);
}