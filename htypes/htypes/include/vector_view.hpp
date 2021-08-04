#ifndef HTYPES_VECTOR_VIEW_INCLUDE_HPP
#define HTYPES_VECTOR_VIEW_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace htps
{
/** Vector class to store a sequence of elements
 * This class is a container to store sequences of Ts. It can be resized.
 * Other use cases include search, replacement, etc...
 */
template <typename T>
class vector_view
{
private:
    T* const buffer_{nullptr};
    size_type const size_{0U};

public:
    using iterator        = T*;
    using const_iterator  = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;

    constexpr vector_view() noexcept = default;
    constexpr vector_view(size_type const size,
                          iterator const iterator) noexcept :
        size_{size}, buffer_{iterator}
    {}

    constexpr vector_view(vector_view const& other) noexcept :
        size_{other.size_}, buffer_{other.buffer_}
    {}

    constexpr vector_view& operator=(vector_view const& other) noexcept = default;

    // Move constructor.
    constexpr vector_view(vector_view&& other) noexcept = default;

    constexpr vector_view& operator=(vector_view&& other) noexcept = default;
};

}  // namespace htps

#endif
