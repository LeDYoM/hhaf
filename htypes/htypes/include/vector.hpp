HTPS_PRAGMA_ONCE
HTPS_PRAGMA_ONCE
#ifndef HTYPES_VECTOR_INCLUDE_HPP
#define HTYPES_VECTOR_INCLUDE_HPP

#include <htypes/include/growpolicy.hpp>
#include <htypes/include/memory/allocator.hpp>
#include <htypes/include/vector_base.hpp>

namespace htps
{
template <typename T,
          typename Allocator  = AllocatorType<T>,
          typename GrowPolicy = GrowPolicyUnary>
using vector = vector_base<T, Allocator, GrowPolicy>;

template <typename T,
          typename Allocator  = AllocatorType<sptr<T>>,
          typename GrowPolicy = GrowPolicyUnary>
using vector_shared_pointers = vector_base<sptr<T>, Allocator, GrowPolicy>;

template <typename T,
          typename Allocator  = AllocatorType<uptr<T>>,
          typename GrowPolicy = GrowPolicyUnary>
using vector_unique_pointers = vector<uptr<T>>;

template <typename T,
          typename Allocator  = AllocatorType<wptr<T>>,
          typename GrowPolicy = GrowPolicyUnary>
using vector_weak_pointers = vector<wptr<T>>;
}  // namespace htps

#endif
