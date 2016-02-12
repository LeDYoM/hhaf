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

	int lib::libMain(int argc, char *argv[])
	{
		argc;
		argv;
		int result = -1;

		try
		{
			initLog();
			installMemManager();
//			zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

			core::HostController hostController(transformParams(argc,argv));
			// WIP:
			uptr<IApp> zpc = std::make_unique<zoper::ZoperProgramController>();
			hostController.addApp(std::move(zpc));

			// End wip
			result = hostController.run();
		}
		catch (lib::excp::BaseException e)
		{
			LOG_DEBUG("Exception: " << e.what());
		}
		finishMemManager();
		finishLog();

		return result;
	}
}
