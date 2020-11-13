#include "execution.hpp"

#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace commander {

static pid_t pid;

SlaveState execute_renderer()
{
	fs::path p = fs::current_path();
	p /= "renderer";

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

void kill_renderer()
{
	if (!pid) {
		return;
	}

	kill(pid, SIGKILL);
}

} // namespace commander
