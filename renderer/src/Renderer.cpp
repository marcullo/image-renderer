#include "Renderer.hpp"

#include "commands.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__RENDERER
#include "logging.hpp"

namespace renderer {

Renderer::Renderer(rand_t& dev) :
	image(dicer_t{dev}, bg_t{255, 255, 255}),
	parser(std::move(sdk::shell::CommandParser::commands_t{commands()}))
{}

void Renderer::process(std::string& command)
{
	auto cmd = parser.parse(command);
	renderer::log_command(cmd);

	switch (CommandType(cmd->type)) {
	case CommandType::SET_WIDTH: {
		const auto& c = std::dynamic_pointer_cast<CommandSetWidth, command_t>(cmd);
		image.set_width(c->w);
		break;
	}

	case CommandType::SET_HEIGHT: {
		const auto& c = std::dynamic_pointer_cast<CommandSetHeight, command_t>(cmd);
		image.set_height(c->h);
		break;
	}

	case CommandType::DRAW_RECTANGLE: {
		const auto& c = std::dynamic_pointer_cast<CommandDrawRectangle, command_t>(cmd);
		image.draw_rectangle(c->x, c->y, c->w, c->h);
		break;
	}

	case CommandType::DRAW_TRIANGLE: {
		const auto& c = std::dynamic_pointer_cast<CommandDrawTriangle, command_t>(cmd);
		image.draw_triangle(c->x1, c->y1, c->x2, c->y2, c->x3, c->y3);
		break;
	}

	case CommandType::RENDER: {
		const auto& c = std::dynamic_pointer_cast<CommandRender, command_t>(cmd);
		image.render(c->filename);
		break;
	}

	default:
		break;
	}
}

} // namespace renderer
