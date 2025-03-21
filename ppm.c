#include "ppm.h"

struct ppm *ppm_read(const char *filename) {
    /*  načte obsah PPM souboru do touto funkcí dynamicky
        alokované struktury. Při chybě formátu použije funkci warning
        a vrátí NULL.  Pozor na "memory leaks".
        */
}

void ppm_free(struct ppm *p) {
    /*         uvolní paměť dynamicky alokovanou v ppm_read */
}