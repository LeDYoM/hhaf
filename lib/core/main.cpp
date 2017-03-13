#include <lib/include/main.hpp>
#include "config.h"
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/exceptions.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	int libMain(int argc, char *argv[], uptr<IApp> app)
	{
		int result = -1;

		try
		{
			initLog();
			installMemManager();

			core::Host::createHost(argc, argv);
			core::Host::host().setApplication(std::move(app));
			result = core::Host::host().run();
			core::Host::destroyHost();
		}
		catch (lib::excp::BaseException e)
		{
			logDebug("BaseException: ", e.what());
		}
		catch (std::exception e)
		{
			logDebug("std::Exception: ", e.what());
		}
		catch (...)
		{
			logDebug("Unexpected exception");
		}
		finishMemManager();
		finishLog();

		return result;
	}
}
