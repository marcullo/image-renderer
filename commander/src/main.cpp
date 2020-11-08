#include <stdio.h>

#include <iostream>
#include <string>

int main(void)
{
	std::string command;

	std::cout << "> ";
	std::getline(std::cin, command);
	std::cout << command << std::endl;

	return EXIT_SUCCESS;
}
