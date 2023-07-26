HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::debug
{
class DebugVariable
{
public:
    using value_type = htps::s64;

    DebugVariable() noexcept;
    DebugVariable(value_type value) noexcept;
    ~DebugVariable();

    DebugVariable(DebugVariable const&);
    DebugVariable(DebugVariable&&);
    DebugVariable& operator=(DebugVariable const&);
    DebugVariable& operator=(DebugVariable&&);

    void incrementFrame() noexcept;
    value_type value() const noexcept;
    htps::u64 frame() const noexcept;
private:
    struct DebugVariablePriv;
    core::PImplPointer<DebugVariablePriv> m_p;
};

}  // namespace haf::debug

#endif