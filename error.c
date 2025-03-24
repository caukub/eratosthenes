// error.c
// Řešení IJC-DU1, příklad A + B, 24. 3. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: Apple clang version 16.0.0 (clang-1600.0.26.3)

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning(const char *fmt, ...) {
    va_list args;

    fprintf(stderr, "Warning: ");

    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;

    fprintf(stderr, "Error: ");

    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}