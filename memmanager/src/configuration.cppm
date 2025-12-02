export module memmanager:configuration;

import parpar.mini;

struct Configuration
{
    bool AlwaysCheckHeap{false};  // Check heap every alloc/dealloc
};

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
