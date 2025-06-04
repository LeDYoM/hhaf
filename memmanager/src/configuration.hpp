#ifndef HAF_MEMMANAGER_CONFIGURATION_INCLUDE_HPP
#define HAF_MEMMANAGER_CONFIGURATION_INCLUDE_HPP

struct Configuration
{
    bool AlwaysCheckHeap{false};  // Check heap every alloc/dealloc
};

Configuration paramsToConfiguration(int const argc, char const* argv[]);
#endif
