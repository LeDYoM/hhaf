#include <haf/include/profiler/memory_data_initializer.hpp>
#include <haf/include/profiler/imemory_data_viewer.hpp>

#include <htypes/include/types.hpp>

#include <memmanager/include/memmanager.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::debug
{
MemoryDataInitializer::MemoryDataInitializer(
    rptr<IMemoryDataViewer> memory_data_viewer) :
    memory_data_viewer_{htps::move(memory_data_viewer)}, is_valid_{false}
{
    if (memory_data_viewer_ != nullptr)
    {
        is_valid_ = memory_data_viewer_->pushMemoryDataStatistics();
    }
}

MemoryDataInitializer::~MemoryDataInitializer()
{
    if (is_valid_)
    {
        auto const allocations_value{allocations()};
        auto const deallocations_value{deallocations()};
        auto const allocatedBytes_value{allocatedBytes()};
        auto const deallocatedBytes_value{deallocatedBytes()};

        is_valid_ = memory_data_viewer_->popMemoryDataStatistics();
        DisplayLog::debug("Allocations: ", allocations_value,
                          "\nDeallocations: ", deallocations_value,
                          "\nBytes allocated: ", allocatedBytes_value,
                          "\nBytes deallocated: ", deallocatedBytes_value);

        LogAsserter::log_assert(is_valid_,
                                "Error destroying MemoryDataInitializer");
    }
}

size_type MemoryDataInitializer::allocations() const
{
    return is_valid_ ? memory_data_viewer_->getHeadAllocations() : 0U;
}

size_type MemoryDataInitializer::deallocations() const
{
    return is_valid_ ? memory_data_viewer_->getHeadDeallocations() : 0U;
}

size_type MemoryDataInitializer::allocatedBytes() const
{
    return is_valid_ ? memory_data_viewer_->getHeadAllocatedByes() : 0U;
}

size_type MemoryDataInitializer::deallocatedBytes() const
{
    return is_valid_ ? memory_data_viewer_->getHeadDeallocatedByes() : 0U;
}

}  // namespace haf::debug
