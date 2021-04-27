#ifndef HTYPES_ALLOCATOR_FUNC_1_INCLUDE_HPP
#define HTYPES_ALLOCATOR_FUNC_1_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <cassert>

namespace htps
{

template <typename T, auto M, auto F>
class AllocatorFunc
{
public:
    using pointer = T*;

    static pointer allocate(const size_type size)
    {
        assert(size > 0U);
        return (pointer)M(sizeof(T) * size);
    }

    static void deallocate(pointer element)
    {
        assert(element != nullptr);
        F(element);
    }
};

}  // namespace htps

#endif
