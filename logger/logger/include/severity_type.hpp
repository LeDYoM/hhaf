#pragma once

#ifndef LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP
#define LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP

namespace logger
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

template <severity_type_t severity_type>
constexpr const auto severity_txt() noexcept
{
    switch (severity_type)
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
    default:
        // That should not happen.
        return "<> :";
    }
}

constexpr severity_type_t compiled_log_severity_type = severity_type_t::all;

using DefaultSeverityType = severity_type_t;

} // namespace logger

#endif
