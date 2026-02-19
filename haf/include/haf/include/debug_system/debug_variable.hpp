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

    value_type value() const noexcept;
    htps::u64 frame() const noexcept;
    htps::f64 valuePerFrame() const noexcept;

    void operator=(value_type const other_value) noexcept;
    void operator+=(value_type const other_value) noexcept;

private:
    value_type m_value;
    htps::u64 m_frame{0U};
};

DebugVariable operator+(DebugVariable const& lhs,
                        DebugVariable::value_type const& rhs);

}  // namespace haf::debug

#endif