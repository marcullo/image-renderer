#include <stdio.h>

#include <iostream>
#include <string>

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMANDER
#define LOG_LEVEL_MODULE_NAME "commander"
#include "logging.hpp"

int main(void)
{
	std::string command;

	std::cout << "> ";
	std::getline(std::cin, command);
	DBG("%s", command.c_str());

	return EXIT_SUCCESS;
}
