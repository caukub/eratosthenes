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