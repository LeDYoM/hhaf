#pragma once

#ifndef MTYPES_ALLOCATOR_INCLUDE_HPP
#define MTYPES_ALLOCATOR_INCLUDE_HPP

#include "placement.hpp"
#include "alloc_func.hpp"

namespace mtps
{

template <typename T>
class AllocatorType : public AllocatorMallocFree<T>,
                      public BasicConstructDestruct<T>
{};

}  // namespace mtps

#endif
