HTPS_PRAGMA_ONCE
#ifndef HTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define HTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <cstdlib>
#include <htypes/include/memory/allocatorfunc.hpp>

namespace htps
{
void free_with_size(void* block, auto const)
{
    std::free(block);
}

template <typename T>
using AllocatorMallocFree =
    AllocatorFunc<T, std::malloc, std::free, free_with_size>;

}  // namespace htps

#endif
