#pragma once

#ifndef HAF_LOGGER_LOG_INCLUDE_HPP
#define HAF_LOGGER_LOG_INCLUDE_HPP

#include <utility>

namespace logger
{
/**
 * @brief Component to facilitate the logging
 * This components provide some easy to use functions and classes
 * to perform a configurable and understandable logging.
 */
template <bool EnableLogs, typename StreamType, typename LogCommiter>
struct Log
{
public:
    /**
     * @brief Statically initializes the log component.
     */
    static void init_log() { LogCommiter::init(); }

    /**
     * @brief Statically destroys the log component.
     */
    static void finish_log() { LogCommiter::finish(); }

    /**
     * @brief Low level log display. This method should not be called
     * directly, it displays a log in any case.
     *
     * @tparam Args Types of the arguments.
     * @param args Arguments to build a line in the log.
     */
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

    /**
     * @brief Low level log display. This method should not be called
     * directly, it displays a log if and only if the condition is true.
     *
     * @tparam Condition Compile time condition.
     * @tparam Args Types of the arguments.
     * @param args Arguments to build a line in the log.
     */
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
