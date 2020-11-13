#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "CommandParser.hpp"

namespace sh = sdk::shell;

namespace renderer {

enum class CommandType : int {
	SET_WIDTH,
	SET_HEIGHT,
	DRAW_RECTANGLE,
	DRAW_TRIANGLE,
	RENDER,
};

struct CommandSetWidth : public sh::Command {
	CommandSetWidth() : Command(int(CommandType::SET_WIDTH), 1) {}
	virtual void decode() {
		this->w = std::stoi(this->args.at(0));
	}
	int w;
};

struct CommandSetHeight : public sh::Command {
	CommandSetHeight() : Command(int(CommandType::SET_HEIGHT), 1) {}
	virtual void decode() {
		this->h = std::stoi(this->args.at(0));
	}
	int h;
};

struct CommandDrawRectangle : public sh::Command {
	CommandDrawRectangle() : Command(int(CommandType::DRAW_RECTANGLE), 4) {}
	virtual void decode() {
		this->x = std::stoi(this->args.at(0));
		this->y = std::stoi(this->args.at(1));
		this->w = std::stoi(this->args.at(2));
		this->h = std::stoi(this->args.at(3));
	}
	int x;
	int y;
	int w;
	int h;
};

struct CommandDrawTriangle : public sh::Command {
	CommandDrawTriangle() : Command(int(CommandType::DRAW_TRIANGLE), 6) {}
	virtual void decode() {
		this->x1 = std::stoi(this->args.at(0));
		this->y1 = std::stoi(this->args.at(1));
		this->x2 = std::stoi(this->args.at(2));
		this->y2 = std::stoi(this->args.at(3));
		this->x3 = std::stoi(this->args.at(4));
		this->y3 = std::stoi(this->args.at(5));
	}
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
};

struct CommandRender : public sh::Command {
	CommandRender() : Command(int(CommandType::RENDER), 1) {}
	virtual void decode() {
		this->filename = this->args.at(0);
	}
	std::string filename;
};

void log_command(sh::CommandParser::command_t& cmd);

const sh::CommandParser::commands_t& commands();

} // namespace renderer

#endif // COMMANDS_HPP
