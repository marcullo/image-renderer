#include <sys/prctl.h>
#include <signal.h>

#include "Channel.hpp"
#include "exceptions.hpp"
#include "Renderer.hpp"

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__RENDERER
#define LOG_LEVEL_MODULE_NAME "renderer"
#include "logging.hpp"

using namespace renderer;
namespace vs = sdk::validation;

int main(void)
{
	sdk::channel::ChannelMOSI mosi{false};
	sdk::channel::ChannelMISO miso{false};
	Renderer::rand_t dev;
	Renderer rr{dev};

	prctl(PR_SET_PDEATHSIG, SIGKILL);

	while (true) {
		try {
			std::string request = mosi.receive();
			rr.process(request);

			std::string ok_response{""};
			miso.send(ok_response);
		}
		catch (vs::VerificationException& e) {
			ERR("%s", e.what());
			std::string response{e.what()};
			miso.send(response);
		}
		catch (std::exception& e) {
			ERR("%s", e.what());
			std::string response{e.what()};
			miso.send(response);
		}
	}

	return EXIT_SUCCESS;
}
