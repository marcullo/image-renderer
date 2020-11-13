#include "validation.hpp"

namespace sdk::validation {

int validate_x(int x, int w)
{
	if (x < origin_x || x >= w) {
		throw LimitException("x", x);
	}

	return x;
}

int validate_y(int y, int h)
{
	if (y < origin_y || y >= h) {
		throw LimitException("y", y);
	}

	return y;
}

int validate_w(int w)
{
	if (w < 0 || w > max_width) {
		throw LimitException("w", w);
	}
	return w;
}

int validate_h(int h)
{
	if (h < 0 || h > max_height) {
		throw LimitException("h", h);
	}
	return h;
}

}  // namespace sdk::validation
