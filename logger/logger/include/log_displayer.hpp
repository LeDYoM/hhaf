#pragma once

#ifndef LIB_LOG_LOG_DISPLAYER_INCLUDE_HPP
#define LIB_LOG_LOG_DISPLAYER_INCLUDE_HPP

#include "severity_type.hpp"

namespace logger
{

template <typename LogClass>
struct LogDisplayer
{
private:
    template <SeverityType::severity_type_t severity_value, typename... Args>
    static constexpr void log_if_severity_under(Args &&... args) noexcept
    {
        log_if<SeverityType::ShowSeverity<severity_value>, severity_value>(
            std::forward<Args>(args)...);
    }

    template <bool condition, SeverityType::severity_type_t severity_value, typename... Args>
    static constexpr void log_if(Args &&... args) noexcept
    {
        if constexpr (condition)
        {
            LogClass::log(
                SeverityType::as_str(severity_value), std::forward<Args>(args)...);
        }
    }

public:
    template <typename... Args>
    static constexpr void info(Args &&... args) noexcept
    {
        log_if_severity_under<SeverityType::severity_type_t::info>(
            std::forward<Args>(args)...);
    }

    template <bool Condition, typename... Args>
    static constexpr void info_if(Args &&... args) noexcept
    {
        log_if_severity_under<Condition ?
            SeverityType::severity_type_t::info :
            SeverityType::severity_type_t::none>(
                std::forward<Args>(args)...);
    }

    template <typename... Args>
    static constexpr void error(Args &&... args) noexcept
    {
        log_if_severity_under<SeverityType::severity_type_t::error>(
            std::forward<Args>(args)...);
    }
};

} // namespace logger

#endif
