#include <haf/include/debug_system/debug_variable.hpp>

using namespace htps;

namespace haf::debug
{

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

void DebugVariable::operator=(value_type const other_value) noexcept
{
    m_value = other_value;
}

void DebugVariable::operator+=(value_type const other_value) noexcept
{
    m_value += other_value;
}

f64 DebugVariable::valuePerFrame() const noexcept
{
    return m_frame ? (static_cast<f64>(m_value) / static_cast<f64>(m_frame))
        : static_cast<f64>(m_value);
}

DebugVariable operator+(DebugVariable const& lhs,
                          DebugVariable::value_type const& rhs)
{
    return DebugVariable{lhs.value() + rhs};
}

DebugVariable operator+(DebugVariable::value_type const& lhs,
                          DebugVariable const& rhs)
{
    return DebugVariable{lhs + rhs.value()};
}

}  // namespace haf::debug
