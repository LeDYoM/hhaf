HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP

#include "system/system_base.hpp"
#include <haf/include/profiler/imemory_data_viewer.hpp>
#include "debug_variables.hpp"

namespace haf::sys
{
class DebugSystem final : public SystemBase,
                          public debug::IMemoryDataViewer,
                          public debug::IMemoryDataCreator
{
    using BaseClass = SystemBase;

public:
    using BaseClass::BaseClass;
    ~DebugSystem();

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
private:
    debug::DebugVariables m_debug_variables;
};

}  // namespace haf::sys

#endif
