#ifndef LOGGING_BACKEND_HPP
#define LOGGING_BACKEND_HPP

#include <cstdio>

#define LOG_LAYOUT "[%s] %s:%s: "
#define LOG_NL "\n"

#define LOG_BACKEND_FN printf

#define LOG_BACKEND_CALL(level, format, ...) \
		LOG_BACKEND_FN(LOG_LAYOUT format LOG_NL, \
		               level, LOG_LEVEL_MODULE_NAME, __func__, ##__VA_ARGS__)

#endif // LOGGING_BACKEND_HPP
