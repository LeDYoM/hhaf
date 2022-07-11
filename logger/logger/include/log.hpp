#ifndef HAF_LOGGER_LOG_INCLUDE_HPP
#define HAF_LOGGER_LOG_INCLUDE_HPP

#include <utility>

namespace logger
{
/**
 * @brief Component to facilitate the logging
 * This components provide some easy to use functions and classes
 * to perform a configurable and understandable logging.
 * @tparam EnableLogs Global log enabling. If false, no logs will be displayed.
 * @tparam StreamType Class supporting stream of strings
 * @tparam LogCommiter Class that will receive the filtered log messages
 */
template <bool EnableLogs, typename StreamType, typename LogCommiter>
struct Log final
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
    static constexpr void log([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (EnableLogs)
        {
            static StreamType log_stream;
            log_stream.clear();
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
    static constexpr void log_if_ce([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            log(std::forward<Args>(args)...);
        }
    }
};

}  // namespace logger

#endif
