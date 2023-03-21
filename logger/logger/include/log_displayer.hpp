#ifndef HAF_LOG_LOG_DISPLAYER_INCLUDE_HPP
#define HAF_LOG_LOG_DISPLAYER_INCLUDE_HPP

#include <utility>

namespace logger
{
static constexpr char const EmptyString[]{""};

template <size_t N>
struct StringLiteral
{
    constexpr StringLiteral(const char (&str)[N])
    {
        for (int i{0}; i < N; ++i)
        {
            value[i] = str[i];
        }
    }

    char value[N];
};

/**
 * @brief Helper class to forward the log calls to a Logger. It makes some
 * assumptions about the @b SeverityType.
 *
 * @tparam LogClass Log class capable of displaying logs.
 */
template <typename LogClass,
          typename SeverityType,
          bool DisplaySeverity_v = false>
struct LogDisplayer
{
    using LogClass_t     = LogClass;
    using SeverityType_t = SeverityType;
    static constexpr bool DisplaySeverity{DisplaySeverity_v};

private:
    /**
     * @brief Private alias for the type of a log severity
     */
    using severity_type_t = typename SeverityType::severity_type_t;

    /**
     * @brief Add a log if the severity is configured to be shown
     *
     * @tparam severity_type Severity of the log
     * @tparam Args... Variadic with types of the the args to be passed to the
     * log function
     * @param args Aguments to pass to the log function
     */
    template <severity_type_t severity_type, typename... Args>
    static constexpr void log_if_show_severity([
        [maybe_unused]] Args&&... args) noexcept
    {
        LogClass::template log_if_ce<
            SeverityType::template ShowSeverity<severity_type>>(
            DisplaySeverity ? SeverityType::template as_str<severity_type>()
                            : "",
            std::forward<Args>(args)...);
    }

public:
    /**
     * @brief Add a debug log
     *
     * @tparam Args... Variadic with types of the the args to be passed to the
     * log function
     * @param args Aguments to pass to the log function
     */
    template <typename... Args>
    static constexpr void debug(Args&&... args) noexcept
    {
        log_if_show_severity<severity_type_t::debug>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void debug_if_ce([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            debug(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void debug_if(bool const cond, Args&&... args) noexcept
    {
        if (cond)
        {
            debug(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void verbose(Args&&... args) noexcept
    {
        log_if_show_severity<severity_type_t::verbose>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void verbose_if_ce([
        [maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            verbose(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void verbose_if(bool const cond, Args&&... args) noexcept
    {
        if (cond)
        {
            verbose(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void info(Args&&... args) noexcept
    {
        log_if_show_severity<severity_type_t::info>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void info_if_ce([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            info(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void info_if(bool const cond, Args&&... args) noexcept
    {
        if (cond)
        {
            info(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void warn(Args&&... args) noexcept
    {
        log_if_show_severity<severity_type_t::warn>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void warn_if_ce([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            warn(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void warn_if(bool const cond, Args&&... args) noexcept
    {
        if (cond)
        {
            warn(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void error(Args&&... args) noexcept
    {
        log_if_show_severity<severity_type_t::error>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void error_if_ce([[maybe_unused]] Args&&... args) noexcept
    {
        if constexpr (Condition)
        {
            error(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    static constexpr void error_if(bool const cond, Args&&... args) noexcept
    {
        if (cond)
        {
            error(std::forward<Args>(args)...);
        }
    }
};

}  // namespace logger

#endif
