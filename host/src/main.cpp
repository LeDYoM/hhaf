#include <host/include/host_export.hpp>
#include <memmanager/include/memmanager.hpp>
#include <host/include/host.hpp>
#include <hlog/include/hlog.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_init.hpp>
#include <host/include/apploader.hpp>

HOST_API int haf_host_main(int argc, char* argv[])
{
    using namespace haf;

    int result = -1;

    try
    {
        installMemManager();

        {
            LogInitializer log_init;
            sys::Host host(argc, argv);
            sys::AppLoader app_loader;
            sys::ManagedApp managed_app = app_loader.loadApp("zoper_game");
            host.setApplication(managed_app.app);
            int run_result(host.run());
            app_loader.unloadApp(managed_app);
            result = run_result;
        }
    }
    catch (std::exception e)
    {
        DisplayLog::error("std::Exception: ", e.what());
    }
    catch (...)
    {
        DisplayLog::info("Unexpected exception");
    }
    finishMemManager();

    return result;
}
