#include <host/include/host.hpp>
#include <hlog/include/hlog.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_init.hpp>
#include <host/include/apploader.hpp>

#ifdef _WIN32
    #define HOST_API extern "C" __declspec(dllexport)
#else
    #define HOST_API extern "C" __attribute__((visibility("default")))
#endif


HOST_API int haf_host_main(int argc, char* argv[])
{
    using namespace haf;
    using namespace haf::host;

    int result = -1;

    try
    {
        {
            LogInitializer log_init;
            Host host(argc, argv);
            AppLoader app_loader;
            ManagedApp managed_app = app_loader.loadApp("Zoper");
            host.setApplication(managed_app.app);
            result = host.run();
            app_loader.unloadApp(managed_app);
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
    return result;
}
