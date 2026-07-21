#include <stdarg.h>

typedef enum { SUCCESS, INFO, WARNING, ERROR } LOG_LEVEL;

const int LEVELS = 4;
char *type[LEVELS] = {"INFO", "SUCCESS", "WARNING", "ERROR"}

char *colors[LEVELS] = {"\x1b[0m", "\x1b[32m", "\x1b[1;33m", "\x1b[31m"};

void logger(LOG_LEVEL level, const *char fmt, ...) { va_list args; }
