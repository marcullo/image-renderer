#include <iostream>

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__RENDERER
#define LOG_LEVEL_MODULE_NAME "renderer"
#include "logging.hpp"

int main(void)
{
	INF("Hello in " BUILD_MODE_STR "!");

	return EXIT_SUCCESS;
}
