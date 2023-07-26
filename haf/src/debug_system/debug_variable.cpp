#include <haf/include/debug_system/debug_variable.hpp>

using namespace htps;

namespace haf::debug
{
DebugVariable::DebugVariable() noexcept = default;

DebugVariable::DebugVariable(value_type value) noexcept :
    m_value{htps::move(value)}
{}

void DebugVariable::incrementFrame() noexcept
{
    ++m_frame;
}

DebugVariable::value_type DebugVariable::value() const noexcept
{
    return m_value;
}

u64 DebugVariable::frame() const noexcept
{
    return m_frame;
}

}  // namespace haf::debug
