HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::debug
{
class DebugVariable
{
public:
    using value_type = htps::s64;

    DebugVariable() noexcept;
    DebugVariable(value_type value) noexcept;
    void incrementFrame() noexcept;

    value_type value() const noexcept;
    htps::u64 frame() const noexcept;

    void operator=(value_type const other_value) noexcept;

private:
    value_type m_value{};
    htps::u64 m_frame{0U};
};

}  // namespace haf::debug

#endif