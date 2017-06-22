#include <lib/include/main.hpp>
#include "config.h"
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <mtypes/include/log.hpp>

namespace lib
{
	int libMain(int argc, char *argv[], uptr<IApp> app)
	{
		int result = -1;

		log::Logger<log::severity_type::info> linfo;
		linfo.log("this is a test", 3);
		try
		{
//			auto *a = loader::createLoader();
			initLog();
			installMemManager();

			core::Host::createHost(argc, argv);
			core::Host::host().setApplication(std::move(app));
			result = core::Host::host().run();
			core::Host::destroyHost();
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
