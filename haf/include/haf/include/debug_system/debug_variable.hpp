HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::debug
{
class DebugVariable
{
public:
    DebugVariable() noexcept;
    DebugVariable(core::str&& value) noexcept;
    DebugVariable(core::str const& value);
    DebugVariable(char const* const value);

    void setValue(core::str&& value) noexcept;
    void setValue(core::str const& value);
    void setValue(char const* const value);

    void incrementFrame() noexcept;
    core::u64 frame() const noexcept;
    core::str const& value() const noexcept;

private:
    core::str m_value;
    core::u64 m_frame{0U};
};

}  // namespace haf::debug

#endif