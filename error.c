#include <stdarg.h>
#include <stdio.h>

void warning(const char *fmt, ...) {
    va_list args;

    fprintf(stderr, "Warning: ");

    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...) {

}