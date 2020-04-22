#pragma once

#ifndef LOGGER_LOG_COUT_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_COUT_COMMITER_INCLUDE_HPP

#include <iostream>

namespace logger
{
struct COutCommiter
{
    static inline void commitlog(const char* const log_stream)
    {
        std::cout << log_stream << std::endl;
        std::cout.flush();
    }
};

}  // namespace logger

#endif
