HTPS_PRAGMA_ONCE
#ifndef HTYPES_ALLOCATOR_MEMMANAGER_MMALLOC_MFREE_INCLUDE_HPP
#define HTYPES_ALLOCATOR_MEMMANAGER_MMALLOC_MFREE_INCLUDE_HPP

#include <htypes/include/memory/allocatorfunc.hpp>
#include <memmanager/include/memmanager.hpp>

namespace htps
{

template <typename T>
using AllocatorMemManagerRaw =
    htps::AllocatorFunc<T, mmalloc, mfree, mfree_with_size>;

}  // namespace htps

#endif
