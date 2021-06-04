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

    static pointer allocate(size_type const size)
    {
        assert(size > 0U);
        return static_cast<pointer>(Allocate(sizeof(T) * size));
    }

    static void deallocate(pointer element)
    {
        assert(element != nullptr);
        Deallocate(element);
    }
/*
    static void deallocate(pointer element, size_type const size)
    {
        assert(element != nullptr);
        Deallocate(element, size);
    }
    */
};

}  // namespace htps

#endif
