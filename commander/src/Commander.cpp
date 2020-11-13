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
	miso(true)
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
	const int size = strlen(response.c_str());

	/* We assume empty response is ok (ack). */
	if (size) {
		throw vs::UnderstandingException(response);
	}

	return !this->commands.empty();
}

} // namespace sdk::shell
