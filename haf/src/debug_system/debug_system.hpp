HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
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

    void init();
    void finish();

    void preUpdate();
    void update();
    void postUpdate();

    debug::MemoryDataInitializer startMemoryCounter() override;

    bool pushMemoryDataStatistics() override;
    bool popMemoryDataStatistics() override;
    bool canAddNode() const noexcept override;

    core::size_type getHeadAllocations() const noexcept override;
    core::size_type getHeadDeallocations() const noexcept override;
    core::size_type getHeadAllocatedByes() const noexcept override;
    core::size_type getHeadDeallocatedByes() const noexcept override;

    debug::DebugVariables& debugVariables();

    void getVariable(debug::DebugVariableHandle& index,
                     char const* const name) override;

    void setVariableValue(debug::DebugVariableHandle const& index,
                          core::str&& value) noexcept override;
    void setVariableValue(debug::DebugVariableHandle const& index,
                          core::str const& value) override;
    void setVariableValue(debug::DebugVariableHandle const& index,
                          char const* const value) override;

private:
    debug::DebugVariables m_debug_variables;
};

}  // namespace haf::sys

#endif
