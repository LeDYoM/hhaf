#include <lib/include/main.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/host.hpp>
#include <lib/include/liblog.hpp>

#include "apploader.hpp"
#include "../zoper_game/app.hpp"

namespace lib
{
    int libMain(int argc, char *argv[])
    {
        int result = -1;

        try
        {
            logger::init_log();

            installMemManager();

            core::Host::createHost(argc, argv);
//          core::AppLoader app_loader;
//          core::Host::host().setApplication(app_loader.loadApp("zooper_game"));
            core::AppUniquePtr app(createApp());
            core::Host::host().setApplication(std::move(app));
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
        logger::finish_log();

        return result;
    }
}
