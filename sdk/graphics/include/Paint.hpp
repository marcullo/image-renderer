#ifndef PAINT_HPP
#define PAINT_HPP

namespace sdk::graphics {

template<class T>
struct Paint {
	/** Setup paint with given colors. */
	Paint(T r, T g, T b) :
		red(r),
		green(g),
		blue(b)
	{}

	/** Setup paint from other instance. */
	Paint(const Paint& p) :
		red(p.red),
		green(p.green),
		blue(p.blue)
	{}

	/** Do not setup paint without explicitly specified colors.  */
	Paint() = delete;

	T red; /** Red color buffer. */
	T green; /** Green color buffer. */
	T blue; /** Blue color buffer. */
};

/** Specify instantiation(s). */
template class Paint<unsigned char>;

} // namespace sdk::graphics

#endif // PAINT_HPP
