#include "configuration.hpp"
#include <parpar/include/parpar_mini.h>

Configuration paramsToConfiguration(int const argc, char const* argv[])
{
    auto const pparser{parparmini::create(argc, argv)};
    Configuration config;
    if (pparser.paramValue("check_all") == "1")
    {
        config.AlwaysCheckHeap = true;
    }
    return config;
}
