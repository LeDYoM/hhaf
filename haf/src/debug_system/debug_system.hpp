HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP

#include "system/system_base.hpp"
#include <haf/include/profiler/imemory_data_viewer.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>
#include "debug_variables.hpp"

namespace haf::sys
{
class DebugSystem final : public SystemBase,
                          public debug::IMemoryDataViewer,
                          public debug::IMemoryDataCreator,
                          public debug::IDebugVariables
{
    using BaseClass = SystemBase;

public:
    static constexpr char StaticTypeName[] = "DebugSystem";

    using BaseClass::BaseClass;
    ~DebugSystem();

    void logBuildStaticData();

    void onStartPreUpdate();
    void onFinishPreUpdate() {}
    void onStartUpdate() {}
    void onFinishUpdate() {}
    void onStartPostUpdate() {}
    void onFinishPostUpdate();

    debug::MemoryDataInitializer startMemoryCounter() override;

    bool pushMemoryDataStatistics() override;
    bool popMemoryDataStatistics() override;
    bool canAddNode() const noexcept override;

    htps::size_type getHeadAllocations() const noexcept override;
    htps::size_type getHeadDeallocations() const noexcept override;
    htps::size_type getHeadAllocatedByes() const noexcept override;
    htps::size_type getHeadDeallocatedByes() const noexcept override;

    debug::DebugVariables& debugVariables();

    void getVariable(debug::DebugVariableHandle& index,
                     char const* const name) override;

    bool getVariableValue(debug::DebugVariableHandle& index,
                          debug::DebugVariable& value) override;

    void incrementVariable(
        debug::DebugVariableHandle const index,
        debug::DebugVariable::value_type const increment =
            static_cast<debug::DebugVariable::value_type>(1)) override;

    void setVariable(
        debug::DebugVariableHandle const index,
        debug::DebugVariable::value_type const newValue =
            static_cast<debug::DebugVariable::value_type>(0)) override;

private:
    debug::DebugVariables m_debug_variables;
};

}  // namespace haf::sys

#endif
