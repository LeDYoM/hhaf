#include <haf/include/debug_system/debug_variable.hpp>

using namespace haf::core;

namespace haf::debug
{
struct DebugVariable::DebugVariablePriv
{
    value_type m_value{};
    htps::u64 m_frame{0U};

//    DebugVariablePriv(value_type a) : m_value{a} {}
};

DebugVariable::~DebugVariable() = default;

DebugVariable::DebugVariable() noexcept :
    m_p{make_pimplp<DebugVariablePriv>()}
{}

DebugVariable::DebugVariable(value_type value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(value)}
{}

DebugVariable::DebugVariable(DebugVariable const&)
    : DebugVariable{}
{

}

DebugVariable::DebugVariable(DebugVariable&&)
    : DebugVariable{}
{

}

DebugVariable& DebugVariable::operator=(DebugVariable const&)
{
    return *this;
}

DebugVariable& DebugVariable::operator=(DebugVariable&&)
{
    return *this;
}

void DebugVariable::incrementFrame() noexcept
{
    ++m_p->m_frame;
}

DebugVariable::value_type DebugVariable::value() const noexcept
{
    return m_p->m_value;
}

u64 DebugVariable::frame() const noexcept
{
    return m_p->m_frame;
}

}  // namespace haf::debug
