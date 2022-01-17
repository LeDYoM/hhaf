#ifndef HTYPES_VECTOR_INCLUDE_HPP
#define HTYPES_VECTOR_INCLUDE_HPP

#include "growpolicy.hpp"
#include "vector_base.hpp"
#include "growpolicy.hpp"
#include "memory/allocator.hpp"

namespace htps
{
template <typename T>
using vector = vector_base<T, AllocatorType<T>, GrowPolicyUnary>;

template <typename T>
using vector_shared_pointers = vector<sptr<T>>;

template <typename T>
using vector_unique_pointers = vector<uptr<T>>;

template <typename T>
using vector_weak_pointers = vector<wptr<T>>;
}  // namespace htps

#endif
