#include <hlog/include/hlog.hpp>
#include "host.hpp"

#include "host_export.hpp"

HOST_PRIVATE int host_main(int argc, char* argv[]) noexcept
{
    using namespace haf;

    int result{-1};

    try
    {
        using namespace haf::host;

        LogInitializer log_init;
        Host host(argc, argv);
        if (host.initialize())
        {
            result = host.run();
        }
    }
    catch (std::exception& e)
    {
        logger::DisplayLog::error("std::Exception: ", e.what());
    }
    catch (...)
    {
        logger::DisplayLog::info("Unexpected exception");
    }
    return result;
}

HOST_API int haf_host_main(int argc, char* argv[])
{
    return host_main(argc, argv);
}
