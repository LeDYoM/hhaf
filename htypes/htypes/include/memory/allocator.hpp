HTPS_PRAGMA_ONCE
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
{
public:
    template <typename... Args>
    static T* make_one(Args&&... args) noexcept(
        noexcept(ReserveDestroy::allocate(1)) && noexcept(
            BasicConstructDestruct<T>::construct(nullptr,
                                                 htps::forward<Args>(args)...)))
    {
        auto t{ReserveDestroy::allocate(1)};
        BasicConstructDestruct<T>::construct(t, htps::forward<Args>(args)...);
        return t;
    }

    static void delete_one(T* pointer) noexcept
    {
        AllocatorType<T>::destruct(pointer);
        AllocatorType<T>::deallocate_with_size(pointer, sizeof(T));
    }

    static void delete_one_from_base(T* pointer) noexcept
    {
        AllocatorType<T>::destruct(pointer);
        AllocatorType<T>::deallocate(pointer);
    }
};

}  // namespace htps

#endif
