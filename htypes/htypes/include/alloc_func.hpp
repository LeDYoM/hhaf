#ifndef MTYPES_ALLOCATOR_MEMMANAGER_MMALLOC_MFREE_INCLUDE_HPP
#define MTYPES_ALLOCATOR_MEMMANAGER_MMALLOC_MFREE_INCLUDE_HPP

#include <mtypes/include/allocatorfunc.hpp>
#include <memmanager/include/memmanager.hpp>

namespace htypes
{

template <typename T>
using AllocatorMemManagerRaw = mtps::AllocatorFunc<T, mmalloc, mfree>;

}  // namespace htypes

#endif
