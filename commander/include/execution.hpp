#ifndef EXECUTION_HPP
#define EXECUTION_HPP

namespace commander {

enum class SlaveState {
	RUN,
	EXITED,
	NOT_RUN,
};

/** Run the slave program. */
SlaveState execute_renderer();

/** Kill the slave program. */
void kill_renderer();

} // namespace commander

#endif // EXECUTION_HPP
