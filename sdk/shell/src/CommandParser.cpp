#include "CommandParser.hpp"

#include <iostream>
#include <regex>

#include "exceptions.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMAND_PARSER
#define LOG_LEVEL_MODULE_NAME "parser"
#include "logging.hpp"

namespace vs = sdk::validation;

namespace sdk::shell {

CommandParser::CommandParser(commands_t&& commands) :
	supported(std::move(commands))
{}

CommandParser::command_t CommandParser::parse(const std::string& command)
{
	DBG("%s", command.c_str());

	this->tokenize(command);

	command_t cmd = this->validate_supported(command);

	this->split_args(cmd);

	const int nargs = cmd->args.size();
	if (cmd->nargs != nargs) {
		ERR("Unexpected nr of args: %u vs %u", nargs, cmd->nargs);
		throw vs::ParsingException{command};
	}

	for (int i = 0; i < nargs; i++) {
		if (cmd->args.at(i).length() == 0) {
			ERR("Argument must not be empty");
			throw vs::ParsingException{command};
		}
	}

	cmd->decode();

	DBG("ok");

	return cmd;
}

void CommandParser::tokenize(const std::string& command)
{
	std::regex pattern{"^(\\w+)\\s+(\\S+)$", std::regex_constants::icase};
	std::smatch m;

	std::regex_search(command, m, pattern);

	if (m.size() != 3) {
		// ERR("Matching groups: %u", m.size());
		throw vs::ParsingException{command};
	}

	this->raw = m[0];
	this->name = m[1];
	this->args = m[2];

	DBG("command: %s", this->name.c_str());
	DBG("args: %s", this->args.c_str());

	/* Ignore command case. */
	for (auto& c : this->name) {
		c = toupper(c);
	}
}

CommandParser::command_t CommandParser::validate_supported(const std::string& command)
{
	try {
		auto cmd = this->supported.at(this->name);
		return cmd;
	}
	catch (std::out_of_range& e) {
		ERR("Unsupported command: %s", this->name.c_str());
		throw vs::ParsingException{command};
	}
}

void CommandParser::split_args(command_t& cmd)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream token_stream{this->args};

	cmd->args.clear();
	while (std::getline(token_stream, token, CommandParser::arg_sep)) {
		cmd->args.push_back(token);
	}
}

} // namespace sdk::shell
