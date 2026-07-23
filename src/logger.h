#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

typedef enum {
  SUCCESS,
  INFO,
  WARNING,
  ERROR
} LOG_LEVEL;

// functions prototypes

void log_event(LOG_LEVEL level, const char * file, int line, const char * text,...);
#endif

#define DEBUG 0
#if DEBUG
#define log_info(fmt, ...) log_event(1, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_warning(fmt, ...) log_event(2, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) log_event(3, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define log_success(fmt, ...) log_event(0, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define log_info(fmt, ...)
#define log_warning(fmt, ...)
#define log_error(fmt, ...)
#define log_success(fmt, ...)
#endif
