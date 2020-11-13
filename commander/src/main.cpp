#include <iostream>

#include "execution.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMANDER
#define LOG_LEVEL_MODULE_NAME "commander"
#include "logging.hpp"

using namespace commander;

int main(void)
{
	if (execute_renderer() != SlaveState::RUN) {
		std::cout << "Failed to fork renderer! Make sure you're located in the same folder as me.";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
