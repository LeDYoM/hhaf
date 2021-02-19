#ifndef HAF_HTYPES_VECTOR_INCLUDE_HPP
#define HAF_HTYPES_VECTOR_INCLUDE_HPP

#include <mtypes/include/vector.hpp>
#include <mtypes/include/allocator.hpp>
#include <htypes/include/alloc_func.hpp>

namespace htps = mtps;

namespace htypes
{
template <typename T>
using vector =
    htps::vector<T, htps::AllocatorType<T, AllocatorMemManagerRaw<T>>>;
};

#endif
