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

template <bool EnableLogs, typename StreamType, typename LogCommiter>
struct Log
{
public:
    static void init_log() { LogCommiter::init(); }

    static void finish_log() { LogCommiter::finish(); }

    template <typename... Args>
    static constexpr void log(Args&&... args) noexcept
    {
        if constexpr (EnableLogs)
        {
            StreamType log_stream;
            LogCommiter::commitlog(
                (log_stream << ... << std::forward<Args>(args)).c_str());
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
