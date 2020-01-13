#pragma once

#ifndef LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP
#define LIB_LOG_SEVERITY_TYPE_INCLUDE_HPP

namespace logger
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
        none,
        debug,
        verbose,
        info,
        error,
    };

    static constexpr const auto as_str(severity_type_t severity_value) noexcept
    {
        switch (severity_value)
        {
        case severity_type_t::debug:
            return "<DEBUG> :";
            break;
        case severity_type_t::verbose:
            return "<VERBOSE> :";
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
    static constexpr bool ShowSeverity = severity_type >= severity_type_t::debug;
};

} // namespace logger

#endif
