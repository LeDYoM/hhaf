#ifndef MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <cstdlib>
#include <mtypes/include/allocatorfunc.hpp>

namespace mtps
{

template <typename T>
using AllocatorMallocFree = AllocatorFunc<T, std::malloc, std::free>;

}  // namespace mtps

#endif
