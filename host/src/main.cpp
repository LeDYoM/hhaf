#include <host/include/host.hpp>
#include <hlog/include/hlog.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_init.hpp>

#ifdef _WIN32
    #define HOST_API extern "C" __declspec(dllexport)
#else
    #define HOST_API extern "C" __attribute__((visibility("default")))
#endif


HOST_API int haf_host_main(int argc, char* argv[])
{
    using namespace haf;
    using namespace haf::host;

    int result{-1};

    try
    {
        LogInitializer log_init;
        Host host(argc, argv);
        if (host.initialize())
        {
            result = host.run();
        }
    }
    catch (std::exception &e)
    {
        DisplayLog::error("std::Exception: ", e.what());
    }
    catch (...)
    {
        DisplayLog::info("Unexpected exception");
    }
    return result;
}
