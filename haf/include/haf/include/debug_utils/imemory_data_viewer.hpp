HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_IMEMORY_DATA_VIEW_INCLUDE_HPP
#define HAF_DEBUG_IMEMORY_DATA_VIEW_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/debug_utils/memory_data_initializer.hpp>

namespace haf::debug
{
class IMemoryDataCreator
{
public:
    virtual MemoryDataInitializer startMemoryCounter() = 0;
protected:
    virtual ~IMemoryDataCreator() = default;
};

class IMemoryDataViewer
{
public:
    virtual bool pushMemoryDataStatistics()  = 0;
    virtual bool popMemoryDataStatistics()   = 0;
    virtual bool canAddNode() const noexcept = 0;

    virtual htps::size_type getHeadAllocations() const noexcept     = 0;
    virtual htps::size_type getHeadDeallocations() const noexcept   = 0;
    virtual htps::size_type getHeadAllocatedByes() const noexcept   = 0;
    virtual htps::size_type getHeadDeallocatedByes() const noexcept = 0;

protected:
    virtual ~IMemoryDataViewer() = default;
};
}  // namespace haf::debug

#endif