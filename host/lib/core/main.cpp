#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/exceptions.hpp>
#include <lib/core/hostcontroller.hpp>
#include <vector>
#include <string>

#include "zoperprogramcontroller.hpp"

namespace lib
{
	namespace
	{
		std::vector<std::string> transformParams(int argc, char *argv[])
		{
			std::vector<std::string> temp;

			for (int i=1;i<argc;++i)
			{
				temp.push_back(argv[i]);
			}
			return temp;
		}
	}

	int libMain(int argc, char *argv[], uptr<IApp> app)
	{
		int result = -1;

		try
		{
			initLog();
			installMemManager();

			core::HostController hostController(transformParams(argc,argv));
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
