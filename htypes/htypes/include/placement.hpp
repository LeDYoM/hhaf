#ifndef MTYPES_PLACEMENT_INCLUDE_HPP
#define MTYPES_PLACEMENT_INCLUDE_HPP

#include <utility>

namespace htps
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

        if constexpr (sizeof...(args) > 0U)
        {
            ::new ((void*)where) T(std::forward<Args>(args)...);
        }
        else
        {
            ::new ((void*)where) T();
        }
    }

    static void construct(pointer where, T const& arg)
    {
        assert(where != nullptr);
        ::new ((void*)where) T(arg);
    }

    static void destruct(pointer where) noexcept
    {
        assert(where != nullptr);
        where->~T();
    }
};

}  // namespace htps

#endif
