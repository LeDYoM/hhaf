#include <haf/include/debug_utils/memory_data_initializer.hpp>
#include <haf/include/debug_utils/imemory_data_viewer.hpp>

#include <htypes/include/types.hpp>

#include <memmanager/include/memmanager.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::debug
{
MemoryDataInitializer::MemoryDataInitializer(
    rptr<IMemoryDataViewer> memory_data_viewer) :
    memory_data_viewer_{std::move(memory_data_viewer)}, is_valid_{false}
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
        is_valid_ = memory_data_viewer_->popMemoryDataStatistics();
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
