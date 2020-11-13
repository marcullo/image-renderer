#ifndef LOGGING_HPP
#define LOGGING_HPP

#define LOG_LEVEL_OFF 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_MIN LOG_LEVEL_ERROR
#define LOG_LEVEL_MAX LOG_LEVEL_DEBUG

#define LOG_TAG_ERR "ERR"
#define LOG_TAG_INF "INF"
#define LOG_TAG_DBG "DBG"

#if defined(LOG_LEVEL)
#if !defined (DEBUG)
#undef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_OFF
#endif // DEBUG
#else
#define LOG_LEVEL LOG_LEVEL_OFF
#endif // LOG_LEVEL

#ifndef LOG_LEVEL_MODULE_NAME
#define LOG_LEVEL_MODULE_NAME ""
#endif

#define LOG_ENABLED_HERE ((LOG_LEVEL) >= LOG_LEVEL_MIN)
#define LOG_ENABLED(level) ((LOG_LEVEL) >= (LOG_LEVEL_##level))

#if LOG_ENABLED_HERE
#include "logging_backend.hpp"
#endif

#if LOG_ENABLED(ERROR)
#define ERR(...) LOG_BACKEND_CALL(LOG_TAG_ERR, ##__VA_ARGS__)
#else
#define ERR(...) { ; }
#endif

#if LOG_ENABLED(INFO)
#define INF(...) LOG_BACKEND_CALL(LOG_TAG_INF, ##__VA_ARGS__)
#else
#define INF(...) { ; }
#endif

#if LOG_ENABLED(DEBUG)
#define DBG(...) LOG_BACKEND_CALL(LOG_TAG_DBG, ##__VA_ARGS__)
#else
#define DBG(...) { ; }
#endif

#endif // LOGGING_HPP
