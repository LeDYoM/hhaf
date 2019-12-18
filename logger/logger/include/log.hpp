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

enum class level_type
{
    debug,
    release
};

constexpr level_type compiled_log_level_type =
#ifndef NDEBUG
    level_type::debug;
#else
    level_type::release;
#endif

template <level_type level>
constexpr bool compile_logs = compiled_log_level_type <= level;

namespace detail
{

inline void commitlog(const char *const log_stream)
{
    std::cout << log_stream << std::endl;
    std::cout.flush();
}

} // namespace detail

template <typename StreamType, typename severity_type_type = DefaultSeverityType>
struct Log
{
    using severity_type = severity_type_type;

    template <level_type level, severity_type severity, typename... Args>
    static constexpr void log(Args &&... args) noexcept
    {
        if constexpr (compile_logs<level> && severity >= compiled_log_severity_type)
        {
            StreamType log_stream(severity_txt<severity>());
            (log_stream << ... << std::forward<Args>(args));
            detail::commitlog(log_stream.c_str());
        }
    }

    template <severity_type severity, typename... Args>
    static constexpr void log_debug(Args &&... args) noexcept
    {
        log<level_type::debug, severity>(std::forward<Args>(args)...);
    }

    template <severity_type severity, typename... Args>
    static constexpr void log_release(Args &&... args) noexcept
    {
        log<level_type::release, severity>(std::forward<Args>(args)...);
    }
};

} // namespace logger

#endif
