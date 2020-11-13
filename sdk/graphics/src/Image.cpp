#include "Image.hpp"

#include "validation.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__IMAGE
#define LOG_LEVEL_MODULE_NAME "image"
#include "logging.hpp"

namespace vn = sdk::validation;

namespace sdk::graphics {

Image::Image(const dicer_t& dr, const paint_t& bg_paint) :
	w(default_size),
	h(default_size),
	bg(bg_paint),
	img(default_size, default_size),
	dicer(dr)
{
	DBG("w %u h %u", this->w, this->h);
	this->clear();
}

void Image::clear()
{
	DBG("resetting colors");
	this->img.set_all_channels(this->bg.red, this->bg.green, this->bg.blue);
}

void Image::set_width(int w)
{
	if (w == this->w) {
		return;
	}

	w = vn::validate_w(w);

	img_t old;
	old.setwidth_height(this->w, this->h);
	old.copy_from(this->img);

	this->img.setwidth_height(w, this->h);

	if (w < this->w) {
		DBG("  cropping x: %u -> %u", this->w, w);
		old.region(0, 0, w, this->h, this->img);
	} else {
		DBG(" extending x: %u -> %u", this->w, w);
		this->clear();
		this->img.copy_from(old, 0, 0);
	}

	this->w = w;
}

void Image::set_height(int h)
{
	if (h == this->h) {
		return;
	}

	h = vn::validate_h(h);

	img_t old;
	old.setwidth_height(this->w, this->h);
	old.copy_from(this->img);

	this->img.setwidth_height(this->w, h);

	if (h < this->h) {
		DBG(" cropping y: %u -> %u", this->h, h);
		old.region(0, 0, this->w, h, this->img);
	} else {
		DBG("extending y: %u -> %u", this->h, h);
		this->clear();
		this->img.copy_from(old, 0, 0);
	}

	this->h = h;
}

void Image::draw_rectangle(int x, int y, int w, int h)
{
	image_drawer draw{this->img};
	const paint_t paint {
		this->dicer(),
		this->dicer(),
		this->dicer()
	};

	w--;
	h--;

	x = vn::validate_x(x, this->w);
	y = vn::validate_y(y, this->h);
	const unsigned int x2 = vn::validate_x(x + w, this->w);
	const unsigned int y2 = vn::validate_x(y + h, this->h);

	draw.pen_color(paint.red, paint.green, paint.blue);
	draw.rectangle(x, y, x2, y2);

	DBG("(%u, %u)[](%u, %u)", x, y, x2, y2);
}

void Image::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	image_drawer draw{this->img};
	const paint_t paint {
		this->dicer(),
		this->dicer(),
		this->dicer()
	};

	vn::validate_x(x1, this->w);
	vn::validate_x(x2, this->w);
	vn::validate_x(x3, this->w);

	vn::validate_y(y1, this->h);
	vn::validate_y(y2, this->h);
	vn::validate_y(y3, this->h);

	draw.pen_color(paint.red, paint.green, paint.blue);
	draw.triangle(x1, y1, x2, y2, x3, y3);

	DBG(" (%u, %u)--(%u, %u)--(%u, %u)", x1, y1, x2, y2, x3, y3);
}

void Image::render(const std::string& filename)
{
	const char* name = filename.c_str();
	this->img.save_image(name);
	DBG("into %s", name);
}

static_assert(Image::default_size <= vn::max_width);
static_assert(Image::default_size <= vn::max_height);

} // namespace sdk::graphics
