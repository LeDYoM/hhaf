#pragma once

#ifndef MTYPES_ALLOCATOR_INCLUDE_HPP
#define MTYPES_ALLOCATOR_INCLUDE_HPP

#include <cassert>
#include "types.hpp"

namespace mtps
{

template <typename T>
class AllocatorMallocFree
{
public:
    using pointer = T *;

    static pointer allocate(const size_type size)
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
    static void construct(pointer where, Args &&... args)
    {
        assert(where != nullptr);
        ::new ((void *)where) T(std::forward<Args>(args)...);
    }

    static void destruct(pointer where) noexcept
    {
        assert(where != nullptr);
        where->~T();
    }
};

} // namespace mtps

#endif
