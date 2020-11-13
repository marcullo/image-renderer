#include "Commander.hpp"

#include <cstring>

#include "exceptions.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMANDER
#include "logging.hpp"

namespace vs = sdk::validation;

namespace commander {

Commander::Commander() :
	mosi(true),
	miso(true),
	log(),
	log_filename("log.txt")
{}

Commander& Commander::operator+=(const std::string& command)
{
	this->commands.push(command);
	return *this;
}

bool Commander::process()
{
	if (this->commands.empty()) {
		return false;
	}

	std::string command{this->commands.front()};
	this->commands.pop();
	this->mosi.send(command);

	auto response = this->miso.receive();
	const char* raw = response.c_str();
	const int size = strlen(raw);

	/* We assume empty response is ok (ack). */
	if (size) {
		if (!log.is_open()) {
			log.open(Commander::log_filename, std::ofstream::app);
		}
		log << raw << std::endl;
		throw vs::UnderstandingException(response);
	}

	return !this->commands.empty();
}

} // namespace sdk::shell
