#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <sstream>
#include <string>

namespace sdk::validation {

class VerificationException : public std::runtime_error {
public:
	VerificationException(const std::string& what) : runtime_error(what) {}
};

class LimitException : public VerificationException {
public:
	LimitException(const char* label, int val) : VerificationException(this->build_error(label, val)) {}

protected:
	std::string build_error(const char* label, int val)
	{
		std::stringstream ss;
		ss << "LimitException: Invalid " << label << " = " << std::to_string(val) << "!";
		return ss.str();
	}
};

} // namespace sdk::exceptions

#endif // EXCEPTIONS_HPP
