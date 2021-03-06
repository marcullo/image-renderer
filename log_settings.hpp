#ifndef LOG_SETTINGS_HPP
#define LOG_SETTINGS_HPP

/** Severity: OFF, ERROR, INFO, DEBUG. */
#define LEVEL(x) LOG_LEVEL_##x

#define LOG_LEVEL__COMMANDER       LEVEL(OFF)
#define LOG_LEVEL__COMMANDS        LEVEL(DEBUG)
#define LOG_LEVEL__RENDERER        LEVEL(OFF)

#define LOG_LEVEL__CHANNEL         LEVEL(OFF)
#define LOG_LEVEL__COMMAND_PARSER  LEVEL(OFF)
#define LOG_LEVEL__IMAGE           LEVEL(OFF)

#endif // LOG_SETTINGS_HPP
