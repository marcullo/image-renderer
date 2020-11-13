#include "commands.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__COMMANDS
#include "logging.hpp"

namespace renderer {

sh::CommandParser::commands_t supported_commands = {
	{"SET_WIDTH", std::dynamic_pointer_cast<sh::Command>(std::make_shared<CommandSetWidth>())},
	{"SET_HEIGHT", std::dynamic_pointer_cast<sh::Command>(std::make_shared<CommandSetHeight>())},
	{"DRAW_RECTANGLE", std::dynamic_pointer_cast<sh::Command>(std::make_shared<CommandDrawRectangle>())},
	{"DRAW_TRIANGLE", std::dynamic_pointer_cast<sh::Command>(std::make_shared<CommandDrawTriangle>())},
	{"RENDER", std::dynamic_pointer_cast<sh::Command>(std::make_shared<CommandRender>())},
};

void log_command(sh::CommandParser::command_t& cmd)
{
	std::string command;
	switch (CommandType(cmd->type)) {
	case CommandType::SET_WIDTH:
		DBG("SET_WIDTH(%u)",
			std::dynamic_pointer_cast<CommandSetWidth, sh::Command>(cmd)->w);
		break;

	case CommandType::SET_HEIGHT:
		DBG("SET_HEIGHT(%u)",
			std::dynamic_pointer_cast<CommandSetHeight, sh::Command>(cmd)->h);
		break;

	case CommandType::DRAW_RECTANGLE: {
		const auto& command = std::dynamic_pointer_cast<CommandDrawRectangle, sh::Command>(cmd);
		DBG("DRAW_RECTANGLE(%u, %u, %u, %u)",
			command->x,
			command->y,
			command->w,
			command->h);
		break;
	}

	case CommandType::DRAW_TRIANGLE: {
		const auto& command = std::dynamic_pointer_cast<CommandDrawTriangle, sh::Command>(cmd);
		DBG("DRAW_TRIANGLE((%u, %u), (%u, %u), (%u, %u))",
			command->x1,
			command->y1,
			command->x2,
			command->y2,
			command->x3,
			command->y3);
		break;
	}

	case CommandType::RENDER:
		DBG("RENDER(%s)",
			std::dynamic_pointer_cast<CommandRender, sh::Command>(cmd)->filename.c_str());
		break;

	default:
		break;
	}
}

const sh::CommandParser::commands_t& commands()
{
	return supported_commands;
}

} // namespace renderer
