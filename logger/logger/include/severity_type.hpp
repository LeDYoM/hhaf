#ifndef HAF_LOG_SEVERITY_TYPE_INCLUDE_HPP
#define HAF_LOG_SEVERITY_TYPE_INCLUDE_HPP

namespace logger
{

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
        none,
        debug,
        verbose,
        info,
        warn,
        error,
    };

#pragma warning(push)
#pragma warning(disable : 4514)  // Unused functions in MSVC

    template <severity_type_t severity_value>
    static constexpr const auto as_str() noexcept
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
            case severity_type_t::warn:
                return "<WARN> :";
                break;
            case severity_type_t::error:
                return "<ERROR> :";
                break;
            case severity_type_t::none:
                return "<NONE?> :";
                break;
            default:
                // That should not happen.
                return "<> :";
        }
    }

#pragma warning(pop)
};

template <typename SeverityType, SeverityType::severity_type_t MinSeverity>
struct SeverityTypeImpl
{
    using severity_type_t = SeverityType::severity_type_t;

    template <severity_type_t severity_value>
    static constexpr const auto as_str() noexcept
    {
        return SeverityType::template as_str<severity_value>();
    }

    template <severity_type_t severity_type>
    static constexpr bool ShowSeverity = (static_cast<int>(severity_type) >=
                                          static_cast<int>(MinSeverity));
};

template <auto severity>
using SeverityTypeActiveTo = SeverityTypeImpl<SeverityTypeDefinition, severity>;

using SeverityType =
    SeverityTypeActiveTo<SeverityTypeDefinition::severity_type_t::debug>;

}  // namespace logger

#endif
