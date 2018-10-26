#include <mtypes/include/types.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/host.hpp>
#include <lib/include/core/log.hpp>
#include <lib/core/logcallback.hpp>

#include "zoper_game/app.hpp"

namespace lib
{
	int libMain(int argc, char *argv[])
	{
		int result = -1;

		try
		{
			log::init_log(defaultUserLogFunction);

			installMemManager();

			core::Host::createHost(argc, argv);
			core::Host::host().setApplication(uptr<IApp>(createApp()));
            int run_result(result = core::Host::host().run());
			core::Host::destroyHost();
            result = run_result;
		}
		catch (std::exception e)
		{
			log_release_error("std::Exception: ", e.what());
		}
		catch (...)
		{
			log_release_info("Unexpected exception");
		}
		finishMemManager();
		log::finish_log();

		return result;
	}
}

int main(int argc, char* argv[])
{
    return lib::libMain(argc, argv);
}
