#ifndef DICE_HPP
#define DICE_HPP

#include <limits>
#include <random>

namespace sdk::dice {

template<class T>
class Dicer {
public:
	Dicer(std::random_device& device) :
		dice(0, std::numeric_limits<T>::max()),
		gen(device())
	{}

	T operator()() { return this->dice(this->gen); }

private:
	std::uniform_int_distribution<T> dice;
	std::mt19937 gen;
};

template class Dicer<unsigned char>;

}; // namespace sdk::dice

#endif // DICE_HPP
