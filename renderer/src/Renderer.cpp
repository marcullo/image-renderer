#include "Renderer.hpp"

#include "commands.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__RENDERER
#include "logging.hpp"

namespace renderer {

Renderer::Renderer() :
	parser(std::move(sdk::shell::CommandParser::commands_t{commands()}))
{}

void Renderer::process(std::string& command)
{
	auto cmd = parser.parse(command);
	renderer::log_command(cmd);
}

} // namespace renderer
