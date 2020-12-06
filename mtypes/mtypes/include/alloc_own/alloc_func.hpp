#ifndef MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <mtypes/include/allocatorfunc1.hpp>
#include <memmanager/include/memmanager.hpp>

namespace mtps
{

template <typename T>
using AllocatorMallocFree = AllocatorFunc1<T, mmalloc, mfree>;

}  // namespace mtps

#endif
