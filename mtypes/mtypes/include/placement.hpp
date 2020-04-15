#pragma once

#ifndef MTYPES_PLACEMENT_INCLUDE_HPP
#define MTYPES_PLACEMENT_INCLUDE_HPP

#include <utility>

namespace mtps
{

template <typename T>
class BasicConstructDestruct
{
public:
    using pointer = T*;

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

}  // namespace mtps

#endif
