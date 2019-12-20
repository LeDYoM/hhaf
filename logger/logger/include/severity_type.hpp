#pragma once

#ifndef LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP
#define LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP

namespace logger_
{

struct SeverityType
{
    ///
    /// Enumerator containing the severity type of the message.
    /// When you use one of the values to ooutput a message, it
    /// will be written if and only if the current severity_type
    /// is bigger or equal to the passed one.
    enum class severity_type_t
    {
        all,
        info,
        error,
        none
    };

    template <severity_type_t severity_value>
    static constexpr const auto as_str() noexcept
    {
        switch (severity_value)
        {
        case severity_type_t::all:
            return "<ALL> :";
            break;
        case severity_type_t::info:
            return "<INFO> :";
            break;
        case severity_type_t::error:
            return "<ERROR> :";
            break;
        case severity_type_t::none:
        default:
            // That should not happen.
            return "<> :";
        }
    }

    template <severity_type_t severity_type>
    static constexpr bool ShowSeverity = severity_type > severity_type_t::all;
};

template <typename LogClass>
struct LogDisplayer
{
    template <bool condition, SeverityType::severity_type_t severity_type, typename... Args>
    static constexpr void log_if(Args &&... args) noexcept
    {
        if constexpr (condition)
        {
            LogClass::log(
                SeverityType::as_str<severity_type>(), std::forward<Args>(args)...);
        }
    }

    template <SeverityType::severity_type_t severity_type, typename... Args>
    static constexpr void log_if_severity_under(Args &&... args) noexcept
    {
        log_if<SeverityType::ShowSeverity<severity_type>, severity_type>(
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    static constexpr void info(Args &&... args) noexcept
    {
        log_if_severity_under<SeverityType::severity_type_t::info>(
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    static constexpr void error(Args &&... args) noexcept
    {
        log_if_severity_under<SeverityType::severity_type_t::error>(
            std::forward<Args>(args)...);
    }
};

} // namespace logger_

using DefaultSeverityType = logger_::SeverityType;

#endif
