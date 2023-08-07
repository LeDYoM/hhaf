#include <haf/include/debug_system/debug_variable.hpp>

using namespace haf::core;

namespace haf::debug
{
DebugVariable::DebugVariable() noexcept = default;

DebugVariable::DebugVariable(str&& value) noexcept : m_value{core::move(value)}
{}

DebugVariable::DebugVariable(str const& value) : m_value{value}
{}

DebugVariable::DebugVariable(char const* const value) : m_value{value}
{}

void DebugVariable::incrementFrame() noexcept
{
    ++m_frame;
}

str const& DebugVariable::value() const noexcept
{
    return m_value;
}

u64 DebugVariable::frame() const noexcept
{
    return m_frame;
}

void DebugVariable::setValue(str&& value) noexcept
{
    m_value = core::move(value);
}

void DebugVariable::setValue(str const& value)
{
    m_value = value;
}

void DebugVariable::setValue(char const* const value)
{
    m_value = value;
}

}  // namespace haf::debug
