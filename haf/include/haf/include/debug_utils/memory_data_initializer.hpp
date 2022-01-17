#ifndef HAF_DEBUG_MEMORY_DATA_INITIALIZER_INCLUDE_HPP
#define HAF_DEBUG_MEMORY_DATA_INITIALIZER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::debug
{
class IMemoryDataViewer;

class HAF_API MemoryDataInitializer
{
public:
    explicit MemoryDataInitializer(
        htps::rptr<IMemoryDataViewer> memory_data_viewer);

    MemoryDataInitializer(MemoryDataInitializer const&) = delete;
    MemoryDataInitializer& operator=(MemoryDataInitializer const&) = delete;

    htps::size_type allocations() const;
    htps::size_type deallocations() const;
    htps::size_type allocatedBytes() const;
    htps::size_type deallocatedBytes() const;

    ~MemoryDataInitializer();

private:
    htps::rptr<IMemoryDataViewer> const memory_data_viewer_;
    bool is_valid_;
};
}  // namespace haf::debug

#endif