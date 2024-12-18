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
    static void init_log()
    {
        if constexpr (EnableLogs)
        {
            StreamType log_stream;
            log_stream().clear();

            LogCommiter::init();
        }
    }

    /**
     * @brief Statically destroys the log component.
     */
    static void finish_log()
    {
        if constexpr (EnableLogs)
        {
            LogCommiter::finish();

            StreamType log_stream;
            log_stream().clear();
        }
    }

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
            StreamType log_stream;
            log_stream().clear();
            (log1(log_stream, std::forward<Args>(args)), ...);
            LogCommiter::commitlog(log_stream().c_str());
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
        if constexpr (Condition && EnableLogs)
        {
            log(std::forward<Args>(args)...);
        }
    }

private:
    template <typename T>
    static constexpr void log1([[maybe_unused]] StreamType& log_stream,
                               [[maybe_unused]] T&& arg) noexcept
    {
        if constexpr (EnableLogs)
        {
            if constexpr (requires { arg(); })
            {
                log_stream() << arg();
            }
            else
            {
                log_stream() << arg;
            }
        }
    }

};

}  // namespace logger

#endif
