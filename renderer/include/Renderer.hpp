#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "CommandParser.hpp"
#include "Dicer.hpp"
#include "Image.hpp"

namespace renderer {

class Renderer {
public:
	using bg_t = sdk::graphics::Image::paint_t;
	using rand_t = std::random_device;

	/** Setup render with random device for foreground color. */
	Renderer(rand_t& dev);

	/** Do not setup renderer from other instances. */
	Renderer(const Renderer&) = delete;

	/** Process provided command. */
	void process(std::string& command);

protected:
	using parser_t = sdk::shell::CommandParser;
	using dicer_t = sdk::graphics::Image::dicer_t;
	using image_t = sdk::graphics::Image;
	using command_t = sdk::shell::Command;

	image_t image; /** Data image object. */
	parser_t parser; /** Command parser. */
};

} // namespace renderer

#endif // RENDERER_HPP
