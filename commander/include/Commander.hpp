#ifndef COMMANDER_HPP
#define COMMANDER_HPP

#include <fstream>
#include <queue>

#include "Channel.hpp"

namespace commander {

class Commander {
public:
	using commands_t = std::queue<std::string>;

	/** Setup commander. */
	Commander();

	/** Do not setup commander from other instance. */
	Commander(const Commander&) = delete;

	/** Add command to be processed. */
	Commander& operator+=(const std::string& command);

	/** Process next command returning busy state. */
	bool process();

protected:
	using output_t = std::ofstream;

	sdk::channel::ChannelMOSI mosi; /** Input communication channel. */
	sdk::channel::ChannelMISO miso; /** Output communication channel. */
	output_t log; /** Log stream to a file. */
	std::string log_filename; /** Log file name. */
	commands_t commands; /** List of commands (if read from file). */
};

} // namespace commander

#endif // COMMANDER_HPP
