#pragma once

#ifndef LIB_LOGCALLBACK_INCLUDE_HPP
#define LIB_LOGCALLBACK_INCLUDE_HPP

#include <lib/include/core/log.hpp>
#include <iostream>

#ifdef _MSC_VER
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

namespace lib
{
    void defaultUserLogFunction(const char*const log_str)
    {
        std::cout << log_str;
        std::cout.flush();
#ifdef _MSC_VER
        OutputDebugString(log_str);
#endif
    }
}

#endif
