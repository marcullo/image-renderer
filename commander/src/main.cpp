#include <iostream>

#include "Commander.hpp"
#include "execution.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMANDER
#define LOG_LEVEL_MODULE_NAME "commander"
#include "logging.hpp"

using namespace commander;

namespace {

int process_from_stdin()
{
	std::string command{""};
	Commander commander;

	while (true) {
		/* Type command. */
		std::cout << "> ";
		if (!std::getline(std::cin, command)) {
			break;
		}

		/* process command. */
		try {
			commander += command;
			commander.process();
		}
		catch (std::exception& e) {
			ERR("%s", e.what());
		}
	}

	return EXIT_SUCCESS;
}

} // namespace

int main(int argc, char* argv[])
{
	(void) argv;

	if (argc > 2) {
		std::cout << "Usage: ./commander [commands_filename]\n";
		return EXIT_FAILURE;
	}

	if (execute_renderer() != SlaveState::RUN) {
		std::cout << "Failed to fork renderer! Make sure you're located in the same folder as me.";
		return EXIT_FAILURE;
	}

	if (argc == 1) {
		return process_from_stdin();
	}

	return EXIT_SUCCESS;
}
