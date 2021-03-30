#ifndef MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <cstdlib>
#include <htypes/include/allocatorfunc.hpp>

namespace htps
{

template <typename T>
using AllocatorMallocFree = AllocatorFunc<T, std::malloc, std::free>;

}  // namespace htps

#endif
