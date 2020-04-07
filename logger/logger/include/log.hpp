#pragma once

#ifndef HAF_LOGGER_LOG_INCLUDE_HPP
#define HAF_LOGGER_LOG_INCLUDE_HPP

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

struct COutCommiter
{
    static inline void commitlog(const char *const log_stream)
    {
        std::cout << log_stream << std::endl;
        std::cout.flush();
    }
};

template <typename StreamType, typename LogCommiter>
struct Log
{
    static constexpr bool output_logs = compile_logs;

public:
    template <typename... Args>
    static constexpr void log(Args &&... args) noexcept
    {
        if constexpr (output_logs)
        {
            StreamType log_stream;
            (log_stream << ... << std::forward<Args>(args));
            LogCommiter::commitlog(log_stream.c_str());
        }
    }
};

} // namespace logger

#endif
