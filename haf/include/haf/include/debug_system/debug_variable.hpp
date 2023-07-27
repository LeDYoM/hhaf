HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::debug
{
enum class DebugVariableType : core::u32
{
    Integer = 0U,
    Float,
    String
};

class DebugVariable
{
public:
    using ValueTypeInteger = core::s64;
    using ValueTypeFloat = core::f64;
    using ValueTypeString = core::str;

    DebugVariable() noexcept;
    DebugVariable(ValueTypeInteger value) noexcept;
    DebugVariable(time::TimePoint value) noexcept;
    DebugVariable(core::s32 value) noexcept;
    DebugVariable(core::u32 value) noexcept;
    DebugVariable(ValueTypeFloat value) noexcept;
    DebugVariable(ValueTypeString value) noexcept;
    DebugVariable(ValueTypeString const& value) noexcept;
    DebugVariable(char const* const value) noexcept;
    ~DebugVariable();

    DebugVariable(DebugVariable const&) = delete;
    DebugVariable& operator=(DebugVariable const&) = delete;
    DebugVariable(DebugVariable&&);
    DebugVariable& operator=(DebugVariable&&);

    void incrementFrame() noexcept;
    ValueTypeInteger valueInteger() const noexcept;
    ValueTypeFloat valueFloat() const noexcept;
    ValueTypeString const& valueString() const noexcept;
    DebugVariableType type() const noexcept;
    core::u64 frame() const noexcept;

    void getStr(core::str& dest) const noexcept;
private:
    struct DebugVariablePriv;
    core::PImplPointer<DebugVariablePriv> m_p;
};

}  // namespace haf::debug

#endif