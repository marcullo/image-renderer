#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "CommandParser.hpp"
#include "Dicer.hpp"

namespace renderer {

class Renderer {
public:
	using rand_t = std::random_device;

	/** Setup render. */
	Renderer();

	/** Do not setup renderer from other instances. */
	Renderer(const Renderer&) = delete;

	/** Process provided command. */
	void process(std::string& command);

protected:
	using parser_t = sdk::shell::CommandParser;
	using command_t = sdk::shell::Command;

	parser_t parser; /** Command parser. */
};

} // namespace renderer

#endif // RENDERER_HPP
