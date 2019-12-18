#pragma once

#ifndef LIB_LOGGER_LOG_INCLUDE_HPP
#define LIB_LOGGER_LOG_INCLUDE_HPP

#include "severity_type.hpp"
#include <iostream>

/**
 * @brief Component to facilitate the logging
 * This components provide some easy to use functions and classes
 * to perform a configurable and understandable logging.
 */
namespace logger
{
inline void init_log() {}
inline void finish_log() {}

constexpr bool compile_logs = true;

namespace detail
{

inline void commitlog(const char *const log_stream)
{
    std::cout << log_stream << std::endl;
    std::cout.flush();
}

} // namespace detail

template <typename StreamType,
    typename severity_type_type = DefaultSeverityType,
    severity_type_type display_log_severity = severity_type_type::all>
struct Log
{
    using severity_type = severity_type_type;

private:
    template <severity_type severity>
    static constexpr bool output_logs = 
        compile_logs && severity >= display_log_severity;

    template <severity_type severity, typename... Args>
    static constexpr void log_imp(Args &&... args) noexcept
    {
        if constexpr (output_logs<severity>)
        {
            StreamType log_stream(severity_txt<severity>());
            (log_stream << ... << std::forward<Args>(args));
            detail::commitlog(log_stream.c_str());
        }
    }

public:
    template <severity_type severity, typename... Args>
    static constexpr void log(Args &&... args) noexcept
    {
        log_imp<severity>(std::forward<Args>(args)...);
    }
};

} // namespace logger

#endif
