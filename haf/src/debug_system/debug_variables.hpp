HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/dictionary.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::debug
{
class DebugVariables final
{
public:
    using DebugVariable_t     = htps::s64;
    using DebugVariableHandle = htps::s64;

    void getVariable(DebugVariableHandle& index, char const* const name);

    bool getVariableValue(DebugVariableHandle& index, DebugVariable_t& value);

    void incrementVariable(
        DebugVariableHandle const index,
        DebugVariable_t const increment = static_cast<DebugVariable_t>(1));

    htps::str state() const;

    void startFrame(time::TimePoint const& now);
    void endFrame();

    htps::size_type size() const noexcept;
    bool empty() const noexcept;

private:
    htps::Dictionary<DebugVariable_t> m_debug_variables;
    time::TimePoint m_last_time_update{0U};
    htps::u64 m_frames{0U};
};

}  // namespace haf::debug

#endif
