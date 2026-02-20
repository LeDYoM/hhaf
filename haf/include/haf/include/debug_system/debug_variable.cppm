export module haf:debug_system:debug_variable;

import :core;

namespace haf::debug
{
class DebugVariable
{
public:
    using value_type = core::s64;

    explicit DebugVariable(value_type value) noexcept m_value{core::move(value)}
    {}

    void incrementFrame() noexcept { ++m_frame; }

    value_type value() const noexcept { return m_value; }

    core::u64 frame() const noexcept;
    {
        return m_frame;
    }

    core::f64 valuePerFrame() const noexcept
    {
        return m_frame ? (static_cast<f64>(m_value) / static_cast<f64>(m_frame))
                       : static_cast<f64>(m_value);
    }

    void operator=(value_type const other_value) noexcept
    {
        m_value = other_value;
    }

    void operator+=(value_type const other_value) noexcept
    {
        m_value += other_value;
    }

private:
    value_type m_value;
    core::u64 m_frame{0U};
};

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
