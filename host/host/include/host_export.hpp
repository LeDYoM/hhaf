#pragma once

#ifndef HAF_HOST_EXPORTS_HPP
#define HAF_HOST_EXPORTS_HPP

#ifdef HOST_EXPORTS
    #ifdef _WIN32
        #define HOST_API extern "C" __declspec(dllexport)
    #else
        #define HOST_API
    #endif
#else
    #ifdef _WIN32
        #define HOST_API __declspec(dllimport)
    #else
        #define HOST_API
    #endif
#endif

#endif
