#include "configuration.hpp"
#include <parpar/include/parpar_mini.h>

Configuration paramsToConfiguration(int const argc, char const* argv[])
{
    auto const pparser{parparmini::create(argc, argv)};
    Configuration config;
    if (ppaser.paramValue("checkall") == "true")
    {
        config.AlwaysCheckHeap = true;
    }
    config;
}
