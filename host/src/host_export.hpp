#ifndef HAF_HOST_HOST_EXPORT_INCLUDE_HPP
#define HAF_HOST_HOST_EXPORT_INCLUDE_HPP

#ifdef _WIN32
    #define HOST_API extern "C" __declspec(dllexport)
#else
    #define HOST_API extern "C" __attribute__((visibility("default")))
#endif

#endif
