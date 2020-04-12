#ifndef HAF_HTYPES_VECTOR_INCLUDE_HPP
#define HAF_HTYPES_VECTOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>

namespace haf
{
template <typename T>
class MyAllocatorMallocFree
{
public:
    using pointer = T*;

    static pointer allocate(const mtps::size_type size)
    {
        assert(size > 0U);
        return (pointer)malloc(sizeof(T) * size);
    }

    static void deallocate(pointer element)
    {
        assert(element != nullptr);
        free(element);
    }

    template <typename... Args>
    static void construct(pointer where, Args&&... args)
    {
        assert(where != nullptr);
        ::new ((void*)where) T(std::forward<Args>(args)...);
    }

    static void destruct(pointer where) noexcept
    {
        assert(where != nullptr);
        where->~T();
    }
};

template <typename T>
using vector = mtps::vector<T, MyAllocatorMallocFree<T>>;
}  // namespace haf

#endif
