// ppm.h
// Řešení IJC-DU1, příklad B, 24. 3. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#define COLORS_IN_PIXEL 3

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);