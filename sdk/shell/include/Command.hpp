#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <memory>
#include <string>
#include <vector>

namespace sdk::shell {

struct Command {
public:
	using args_t = std::vector<std::string>;
	using ptr_t = std::shared_ptr<Command>;

	/** Setup command with type and expected nargs. */
	Command(int t, int nargs) :
		type(t),
		nargs(nargs)
	{}

	/** Do not setup command from other instance. */
	Command(const Command&) = delete;

	/** Specify decoding. */
	virtual void decode() = 0;

	virtual ~Command() {}

	int type; /** Command type. */
	int nargs; /** Expected nr of arguments. */
	args_t args; /** Raw arguments. */
};

} // namespace sdk::shell

#endif // COMMAND_HPP
