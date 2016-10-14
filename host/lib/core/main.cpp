#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/exceptions.hpp>
#include <lib/core/hostcontroller.hpp>

namespace lib
{
	int libMain(int argc, char *argv[], uptr<IApp> app)
	{
		int result = -1;

		try
		{
			initLog();
			installMemManager();

			core::HostController hostController(argc,argv);
			hostController.setApp(std::move(app));
			result = hostController.run();
		}
		catch (lib::excp::BaseException e)
		{
			LOG_DEBUG("BaseException: " << e.what());
		}
		catch (std::exception e)
		{
			LOG_DEBUG("BaseException: " << e.what());
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
