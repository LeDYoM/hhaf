#ifndef HAF_LOG_SEVERITY_TYPE_INCLUDE_HPP
#define HAF_LOG_SEVERITY_TYPE_INCLUDE_HPP

namespace logger
{
/**
 * @brief Encapsulate the severity enumeration and related small functions.
 */
struct SeverityTypeDefinition
{
    /**
     * @brief Enumerator containing the severity type of the message.
     * When you use one of the values to ooutput a message, it
     * will be written if and only if the current severity_type
     * is bigger or equal to the passed one.
     */
    enum class severity_type_t
    {
        none = 0U,
        debug,
        verbose,
        info,
        warn,
        error,
    };

    /**
     * @brief Convert a severity_type_t passed as parameter to a string
     * @tparam severity_value
     * @return The string
     */
    static consteval const auto as_str(
        const severity_type_t severity_value) noexcept
    {
        switch (severity_value)
        {
            case severity_type_t::debug:
                return "<DEBUG>: ";
                break;
            case severity_type_t::verbose:
                return "<VERBOSE>: ";
                break;
            case severity_type_t::info:
                return "<INFO>: ";
                break;
            case severity_type_t::warn:
                return "<WARN>: ";
                break;
            case severity_type_t::error:
                return "<ERROR>: ";
                break;
            case severity_type_t::none:
                return "<NONE?>: ";
                break;
            default:
                // That should not happen.
                return "<>: ";
        }
    }
};

template <typename SeverityType, SeverityType::severity_type_t MinSeverity>
struct SeverityTypeImpl
{
    using severity_type_t = SeverityType::severity_type_t;

    static consteval const auto as_str(severity_type_t severity_value) noexcept
    {
        return SeverityType::as_str(severity_value);
    }

    static consteval bool showSeverity(severity_type_t severity_type) noexcept
    {
        return (static_cast<int>(severity_type) >=
                static_cast<int>(MinSeverity));
    }
};

template <auto severity>
using SeverityTypeActiveTo = SeverityTypeImpl<SeverityTypeDefinition, severity>;

using SeverityType =
    SeverityTypeActiveTo<SeverityTypeDefinition::severity_type_t::debug>;

}  // namespace logger

#endif
