#ifndef HAF_HTYPES_VECTOR_INCLUDE_HPP
#define HAF_HTYPES_VECTOR_INCLUDE_HPP

#include <mtypes/include/vector.hpp>

namespace haf
{
template <typename T,
          typename Allocator  = mtps::AllocatorType<T>,
          typename GrowPolicy = mtps::GrowPolicyUnary>
    using vector = mtps::vector<T, Allocator, GrowPolicy>;
}

#endif
