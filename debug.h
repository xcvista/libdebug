#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern int debug_level;     // = DEBUG_LEVEL_WARNING
extern int log_level;       // = DEBUG_LEVEL_INFO
#define DEBUG_LEVEL_ERROR (5)
#define DEBUG_LEVEL_WARNING (4)
#define DEBUG_LEVEL_INFO (3)
#define DEBUG_LEVEL_VERBOSE (2)
#define DEBUG_LEVEL_DEBUG (1)
#define DEBUG_LEVEL_DETAIL (0)

extern FILE *debug_file;    // = stderr
extern FILE *log_file;      // = NULL

extern int vlprintf(int level, char *format, va_list args);
extern int veprintf(char *format, va_list args);
extern int lprintf(int level, char *format, ...) __attribute__((format(printf, 2, 3)));
extern int eprintf(char *format, ...) __attribute__((format(printf, 1, 2)));

#define eprintfc(format, ...) do { eprintf(format, ##__VA_ARGS__); abort(); } while (0)
#define eprintfe(rv, format, ...) do { eprintf(format, ##__VA_ARGS__); exit(rv); } while (0)

#define wprintf(format, ...) lprintf(DEBUG_LEVEL_WARNING, format, ##__VA_ARGS__)
#define iprintf(format, ...) lprintf(DEBUG_LEVEL_INFO, format, ##__VA_ARGS__)
#define pverbose(format, ...) lprintf(DEBUG_LEVEL_VERBOSE, format, ##__VA_ARGS__)

#if defined(DEBUG)
#define pdebug(format, ...) lprintf(DEBUG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#else
#define pdebug(format, ...) do {} while (0)
#endif

#if defined(__cplusplus)
}
#endif

#endif // DEBUG_H_INCLUDED
