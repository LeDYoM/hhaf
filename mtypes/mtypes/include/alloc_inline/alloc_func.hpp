#pragma once

#ifndef MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP
#define MTYPES_ALLOCATOR_MALLOC_FREE_INCLUDE_HPP

#include <cstdlib>
#include <mtypes/include/allocatorfunc1.hpp>

namespace mtps
{

template <typename T>
using AllocatorMallocFree = AllocatorFunc1<T, std::malloc, std::free>;

}  // namespace mtps

#endif
