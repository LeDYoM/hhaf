#ifndef LOADER_EXPORTS_HPP
#define LOADER_EXPORTS_HPP

#ifdef loader_EXPORTS
    #ifdef _WIN32
        #define LOADER_API __declspec(dllexport)
    #else
        #define LOADER_API
    #endif
#else
    #ifdef _WIN32
        #define LOADER_API __declspec(dllimport)
    #else
        #define LOADER_API
    #endif
#endif

#endif
