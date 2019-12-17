#pragma once

#ifndef LIB_MTYPES_LOG_INCLUDE_HPP
#define LIB_MTYPES_LOG_INCLUDE_HPP

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

/**
     * Enumerator containing the severity type of the message.
     * When you use one of the values to ooutput a message, it
     * will be written if and only if the current severity_type
     * is bigger or equal to the passed one.
     */
enum class severity_type
{
    all,
    info,
    error,
    none
};

constexpr level_type compiled_log_level_type =
#ifndef NDEBUG
    level_type::debug;
#else
    level_type::release;
#endif

constexpr severity_type compiled_log_severity_type = severity_type::all;

template <level_type level>
constexpr bool compile_logs = compiled_log_level_type <= level;

namespace detail
{
template <severity_type severity>
constexpr const auto severity_txt() noexcept
{
    switch (severity)
    {
    case severity_type::all:
        return "<ALL> :";
        break;
    case severity_type::info:
        return "<INFO> :";
        break;
    case severity_type::error:
        return "<ERROR> :";
        break;
    default:
        // That should not happen.
        return "<> :";
    }
}

inline void commitlog(const char *const log_stream)
{
    std::cout << log_stream << std::endl;
    std::cout.flush();
}

template <typename StreamType, typename... Args>
void to_log_stream(StreamType &sout, Args &&... args)
{
    (sout << ... << args);
}
} // namespace detail

template <typename StreamType>
struct Log
{
    template <level_type level, severity_type severity, typename... Args>
    static constexpr void log(Args &&... args) noexcept
    {
        if constexpr (compile_logs<level> && severity >= compiled_log_severity_type)
        {
            StreamType log_stream(detail::severity_txt<severity>());
            detail::to_log_stream(log_stream, std::forward<Args>(args)...);
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
