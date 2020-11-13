#include "execution.hpp"

#include <limits.h>
#include <unistd.h>
#include <sys/types.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace commander {

SlaveState execute_renderer()
{
	fs::path p = fs::current_path();
	p /= "renderer";

	static pid_t pid;
	char* args[] = { NULL };

	pid = fork();
	if (pid == 0) {
		execvp(p.c_str(), args);
		return SlaveState::EXITED;
	} else if (pid > 0) {
		return SlaveState::RUN;
	}

	return SlaveState::NOT_RUN;
}

} // namespace commander
