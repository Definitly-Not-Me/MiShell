
#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

void log_event(LOG_LEVEL level, const char *file, int line, const char *text,
               ...) {
  if (!text) {
    fprintf(stderr, "Invalid log message\n");
    return;
  };

  char *color_level[4] = {
      "\x1b[32m",
      "\x1b[37m",
      "\x1b[33m",
      "\x1b[31m",
  };
  char *type;
  switch (level) {
  case 0:
    type = "SUCCESS";
    break;
  case 1:
    type = "INFO";
    break;
  case 2:
    type = "WARNING";
    break;
  case 3:
    type = "ERROR";
    break;
  default:
    type = "UNEXPECTED";
    break;
  };

  printf("%s", (level < 4) ? color_level[level] : color_level[1]);

  printf("[%s]%s:%d\t", type, file, line);

  va_list args;
  va_start(args, text);
  vprintf(text, args);
  va_end(args);

  printf("\x1b[m\n");
  return;
}
