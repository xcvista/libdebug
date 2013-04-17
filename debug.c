#include "debug.h"

int debug_level;
int log_level;

FILE *debug_file;
FILE *log_file;

void __debug_init() __attribute__((constructor));

void __debug_init()
{
    char *buf = NULL;

    if ((buf = getenv("LIBDEBUG_DEBUG_LEVEL")))
        debug_level = (int)strtol(buf, NULL, 10);
    else
        debug_level = DEBUG_LEVEL_WARNING;

    if ((buf = getenv("LIBDEBUG_LOG_LEVEL")))
        log_level = (int)strtol(buf, NULL, 10);
    else
        log_level = DEBUG_LEVEL_INFO;

    debug_file = stderr;
    log_file = NULL;
}

int vflprintf(int level, FILE *file, char *format, va_list args)
{
    if (!file)
        return 0;

    static char *levels[] = {"DETAIL", "DEBUG", "VERBOSE", "INFO", "WARNING", "ERROR"};
    if (level < 6)
        fprintf(file, "[%s] ", levels[level]);
    else
        fprintf(file, "[ERROR %d] ", level);

    int rv = vfprintf(file, format, args);
    fputc('\n', file);
    fflush(file);
    return rv;
}

int vlprintf(int level, char *format, va_list args)
{
    int rv1 = (level >= debug_level) ? vflprintf(level, debug_file, format, args) : 0;
    int rv2 = (level >= log_level) ? vflprintf(level, log_file, format, args) : 0;
    return (rv1 > rv2) ? rv1 : rv2;
}

int veprintf(char *format, va_list args)
{
    lprintf(DEBUG_LEVEL_ERROR, "%s", strerror(errno));
    return vlprintf(DEBUG_LEVEL_ERROR, format, args);
}

int lprintf(int level, char *format, ...)
{
    va_list args;
    va_start(args, format);
    int rv = vlprintf(level, format, args);
    va_end(args);
    return rv;
}

int eprintf(char *format, ...)
{
    va_list args;
    va_start(args, format);
    int rv = veprintf(format, args);
    va_end(args);
    return rv;
}

