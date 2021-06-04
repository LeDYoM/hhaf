#ifndef HTYPES_ALLOCATOR_FUNC_1_INCLUDE_HPP
#define HTYPES_ALLOCATOR_FUNC_1_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <cassert>

namespace htps
{

template <typename T, auto Allocate, auto Deallocate>
class AllocatorFunc
{
public:
    using pointer = T*;

    static pointer allocate(const size_type size)
    {
        assert(size > 0U);
        return (pointer)Allocate(sizeof(T) * size);
    }

    static void deallocate(pointer element)
    {
        assert(element != nullptr);
        Deallocate(element);
    }
};

}  // namespace htps

#endif
