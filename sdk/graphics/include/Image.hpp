#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

#include "bitmap/bitmap_image.hpp"

#include "Dicer.hpp"
#include "Paint.hpp"

namespace sdk::graphics {

class Image {
public:
	/** Set color depth. */
	using color_t = unsigned char;

	/** Specify input types. */
	using paint_t = Paint<color_t>;
	using dicer_t = sdk::dice::Dicer<color_t>;

	/** Specify default size. */
	static const int default_size = 500;

	/** Setup image with pixel color randomizer and static background. */
	Image(const dicer_t& dr, const paint_t& bg_paint);

	/** Do not setup image without pixel color randomizer. */
	Image() = delete;

	/** Do not setup image from other instance as it is not implemented yet. */
	Image(const Image& img) = delete;

	/** Clear the image so it has background only. */
	void clear();

	/** Set width of image. Throw LimitException if w is invalid. */
	void set_width(int w);

	/** Set height of image. Throw LimitException if h is invalid. */
	void set_height(int h);

	/** Draw rectangle with random color. Throw LimitException if outside the window. */
	void draw_rectangle(int x, int y, int w, int h);

	/** Draw triangle with random color. Throw LimitException if outside the window. */
	void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

	/** Render the image into a file. */
	void render(const std::string& filename);

protected:
	using img_t = bitmap_image;

	int w; /** Cached image width. */
	int h; /** Cached image height. */
	paint_t bg; /** Background color. */
	img_t img; /** Slave image object with image data. */
	dicer_t dicer; /** Color randomizer. */
};

} // namespace sdk::graphics

#endif // IMAGE_HPP
