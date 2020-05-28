#ifndef HAF_HLOG_EXPORTS_HPP
#define HAF_HLOG_EXPORTS_HPP

#ifdef HLOG_EXPORTS
    #ifdef _WIN32
        #define HLOG_API __declspec(dllexport)
    #else
        #define HLOG_API
    #endif
#else
    #ifdef _WIN32
        #define HLOG_API __declspec(dllimport)
    #else
        #define HLOG_API
    #endif
#endif

#endif
