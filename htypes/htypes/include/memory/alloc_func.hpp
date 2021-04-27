#ifndef HTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define HTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <cstdlib>
#include <htypes/include/memory/allocatorfunc.hpp>

namespace htps
{

template <typename T>
using AllocatorMallocFree = AllocatorFunc<T, std::malloc, std::free>;

}  // namespace htps

#endif
