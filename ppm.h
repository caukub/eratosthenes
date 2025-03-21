struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);