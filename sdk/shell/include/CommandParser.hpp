#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <unordered_map>

#include "Command.hpp"

namespace sdk::shell {

class CommandParser {
public:
	using command_t = Command::ptr_t;
	using commands_t = std::unordered_map<std::string, command_t>;

	static const char arg_sep = ','; /** Arguments delimiter. */

	/** Setup supported list of commands. */
	CommandParser(commands_t&& commands);

	/** Do not setup parser without list of supported commands. */
	CommandParser() = delete;

	/** Parse raw command. */
	command_t parse(const std::string& command);

protected:
	/** Split message into tokens (command and its arguments). */
	void tokenize(const std::string& command);

	/** Get supported Command if supported. */
	command_t validate_supported(const std::string& command);

	/** Split arguments from raw string. */
	void split_args(command_t& cmd);

	commands_t supported; /** Supported commands. */
	std::string raw; /** Raw message. */
	std::string name; /** Decoded command name. */
	std::string args; /** Decoded command args (raw string). */
};

} // namespace sdk::shell

#endif // COMMAND_PARSER_HPP
