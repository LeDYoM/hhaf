#include <haf/include/debug_system/debug_variable.hpp>

using namespace haf::core;

namespace haf::debug
{
struct DebugVariable::DebugVariablePriv
{
    core::u64 m_frame{0U};
    ValueTypeInteger m_value_integer{};
    ValueTypeFloat m_value_float{};
    ValueTypeString m_value_string{};
    DebugVariableType m_variableType{DebugVariableType::Unknown};

    DebugVariablePriv() noexcept = default;

    DebugVariablePriv(ValueTypeInteger&& value) noexcept :
        m_value_integer{core::move(value)},
        m_variableType{DebugVariableType::Integer}
    {}

    DebugVariablePriv(ValueTypeFloat value) noexcept :
        m_value_float{value}, m_variableType{DebugVariableType::Float}
    {}

    DebugVariablePriv(ValueTypeString&& value) noexcept :
        m_value_string{core::move(value)},
        m_variableType{DebugVariableType::String}
    {}

    DebugVariablePriv(ValueTypeString const& value) noexcept :
        m_value_string{value}, m_variableType{DebugVariableType::String}
    {}
};

DebugVariable::DebugVariable() noexcept : m_p{make_pimplp<DebugVariablePriv>()}
{}

DebugVariable::DebugVariable(time::TimePoint value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(
        static_cast<core::s64>(value.nanoseconds()))}
{}

DebugVariable::DebugVariable(core::s32 value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(static_cast<core::s64>(value))}
{}

DebugVariable::DebugVariable(core::u32 value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(static_cast<ValueTypeInteger>(value))}
{}

DebugVariable::DebugVariable(ValueTypeInteger value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(core::move(value))}
{}

DebugVariable::DebugVariable(ValueTypeFloat value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(core::move(value))}
{}

DebugVariable::DebugVariable(ValueTypeString&& value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(core::move(value))}
{}

DebugVariable::DebugVariable(ValueTypeString const& value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(value)}
{}

DebugVariable::DebugVariable(char const* const value) noexcept :
    m_p{make_pimplp<DebugVariablePriv>(core::str{value})}
{}

DebugVariable::~DebugVariable() = default;

DebugVariable::DebugVariable(DebugVariable&&) = default;
DebugVariable& DebugVariable::operator=(DebugVariable&&) = default;

void DebugVariable::incrementFrame() noexcept
{
    ++m_p->m_frame;
}

DebugVariable::ValueTypeInteger DebugVariable::valueInteger() const noexcept
{
    return m_p->m_value_integer;
}

DebugVariable::ValueTypeFloat DebugVariable::valueFloat() const noexcept
{
    return m_p->m_value_float;
}

DebugVariable::ValueTypeString const& DebugVariable::valueString()
    const noexcept
{
    return m_p->m_value_string;
}

u64 DebugVariable::frame() const noexcept
{
    return m_p->m_frame;
}

void DebugVariable::setValue(ValueTypeInteger value) noexcept
{
    m_p->m_value_integer = value;
    m_p->m_variableType  = DebugVariableType::Integer;
}

void DebugVariable::setValue(time::TimePoint value) noexcept
{
    m_p->m_value_integer = static_cast<ValueTypeInteger>(value.nanoseconds());
    m_p->m_variableType  = DebugVariableType::Integer;
}

void DebugVariable::setValue(core::s32 value) noexcept
{
    m_p->m_value_integer = static_cast<ValueTypeInteger>(value);
    m_p->m_variableType  = DebugVariableType::Integer;
}

void DebugVariable::setValue(core::u32 value) noexcept
{
    m_p->m_value_integer = static_cast<ValueTypeInteger>(value);
    m_p->m_variableType  = DebugVariableType::Integer;
}

void DebugVariable::setValue(ValueTypeFloat value) noexcept
{
    m_p->m_value_float  = value;
    m_p->m_variableType = DebugVariableType::Float;
}

void DebugVariable::setValue(ValueTypeString&& value) noexcept
{
    m_p->m_value_string = core::move(value);
    m_p->m_variableType = DebugVariableType::String;
}

void DebugVariable::setValue(ValueTypeString const& value) noexcept
{
    m_p->m_value_string = value;
    m_p->m_variableType = DebugVariableType::String;
}

void DebugVariable::setValue(char const* const value) noexcept
{
    m_p->m_value_string = value;
    m_p->m_variableType = DebugVariableType::String;
}

void DebugVariable::getStr(core::str& dest) const noexcept
{
    switch (m_p->m_variableType)
    {
        case DebugVariableType::Unknown:
            dest = "Unknown";
            break;
        case DebugVariableType::Integer:
            dest = core::str::to_str(m_p->m_value_integer);
            break;
        case DebugVariableType::Float:
            dest = core::str::to_str(m_p->m_value_float);
            break;
        case DebugVariableType::String:
            dest = m_p->m_value_string;
            break;
    }
}

void DebugVariable::setValueFrom(
    DebugVariable const& debug_variable_value) noexcept
{
    *(this->m_p) = *(debug_variable_value.m_p);
}

void DebugVariable::setValueFrom(DebugVariable&& debug_variable_value) noexcept
{
    *(this->m_p) = core::move(*(debug_variable_value.m_p));
}

DebugVariableType DebugVariable::type() const noexcept
{
    return m_p->m_variableType;
}

}  // namespace haf::debug
