#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
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
			LOG_DEBUG("BaseException: ", e.what());
		}
		catch (std::exception e)
		{
			LOG_DEBUG("std::Exception: ", e.what());
		}
		catch (...)
		{
			LOG_DEBUG("Unexpected exception");
		}
		finishMemManager();
		finishLog();

		return result;
	}
}
