#pragma once

#ifndef HAF_EXPORTER_EXPORTS_INCLUDE_HPP
#define HAF_EXPORTER_EXPORTS_INCLUDE_HPP

#ifdef HOST_EXPORTS
    #ifdef _WIN32
        #define HOST_API __declspec(dllexport)
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
