#pragma once

#ifndef HAF_LOGGER_LOG_INCLUDE_HPP
#define HAF_LOGGER_LOG_INCLUDE_HPP

/**
 * @brief Component to facilitate the logging
 * This components provide some easy to use functions and classes
 * to perform a configurable and understandable logging.
 */
namespace logger
{
constexpr bool compile_logs = true;

template <bool EnableLogs, typename StreamType, typename LogCommiter>
struct Log
{
public:
    static void init_log() {}
    static void finish_log() {}

    template <typename... Args>
    static constexpr void log(Args&&... args) noexcept
    {
        if constexpr (EnableLogs)
        {
            StreamType log_stream;
            (log_stream << ... << std::forward<Args>(args));
            LogCommiter::commitlog(log_stream.c_str());
        }
    }

    template <bool Condition, typename... Args>
    static constexpr void log_if(Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            log(std::forward<Args>(args)...);
        }
    }
};

}  // namespace logger

#endif
