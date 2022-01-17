#ifndef HTYPES_ALLOCATOR_INCLUDE_HPP
#define HTYPES_ALLOCATOR_INCLUDE_HPP

#include "placement.hpp"

#ifdef USER_MEM_MANAGER
#include "alloc_func_memmanager.hpp"
template <typename T>
using ReserveDestroyT = htps::AllocatorMemManagerRaw<T>;
#else
#include "alloc_func.hpp"
template <typename T>
using ReserveDestroyT = htps::AllocatorMallocFree<T>;
#endif

namespace htps
{

template <typename T, typename ReserveDestroy = ReserveDestroyT<T>>
class AllocatorType : public ReserveDestroy, public BasicConstructDestruct<T>
{};

}  // namespace htps

#endif
