HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "debug_log.hpp"

namespace haf::debug
{
class DebugVariable final
{
public:
    using DebugVariable_t = htps::f64;

    explicit constexpr DebugVariable() noexcept = default;
    explicit constexpr DebugVariable(DebugVariable_t const value) noexcept :
        m_value{value}, m_accumulate{}
    {}

    constexpr DebugVariable& operator=(DebugVariable_t const value) noexcept
    {
        m_value = value;
        return *this;
    }

    constexpr DebugVariable(DebugVariable const&) noexcept = default;
    constexpr DebugVariable(DebugVariable&&) noexcept      = default;
    constexpr DebugVariable& operator=(DebugVariable const&) noexcept = default;
    constexpr DebugVariable& operator=(DebugVariable&&) noexcept = default;

    void updateReset(htps::u64 const samples) noexcept
    {
        DebugLogDisplayer::debug("samples: ", samples);
        DebugLogDisplayer::debug("m_value: ", m_value);
        DebugVariable_t temp{m_value / static_cast<DebugVariable_t>(samples)};
        DebugLogDisplayer::debug("temp: ", temp);
        m_accumulate = (m_accumulate + temp) / static_cast<DebugVariable_t>(
            m_accumulate == DebugVariable_t{} ? 1 : 2);
        m_value      = DebugVariable_t{};
        DebugLogDisplayer::debug("m_accumulate: ", m_accumulate);
        DebugLogDisplayer::debug("-------------------: ");
    }

    constexpr htps::f64 currentValue() const noexcept { return m_value; }
    constexpr htps::f64 accumulated() const noexcept
    {
        return m_accumulate;
    }

private:
    htps::f64 m_value;
    htps::f64 m_accumulate;
};

}  // namespace haf::debug

#endif
