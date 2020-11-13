#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "exceptions.hpp"

namespace sdk::validation {

const int max_width = 8192;
const int max_height = 8192;
const int origin_x = 0;
const int origin_y = 0;

int validate_x(int x, int w);
int validate_y(int x, int w);
int validate_w(int w);
int validate_h(int h);

} // namespace sdk::validation

#endif // VALIDATOR_HPP
