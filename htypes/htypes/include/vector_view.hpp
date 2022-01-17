#ifndef HTYPES_VECTOR_VIEW_INCLUDE_HPP
#define HTYPES_VECTOR_VIEW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/vector_storage.hpp>
#include <htypes/include/vector_base.hpp>

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

    constexpr vector_view(iterator const iterator,
                          size_type const size) noexcept :
        buffer_{iterator}, size_{size}
    {}

    template <typename Allocator, typename GrowPolicy>
    constexpr vector_view(
        vector_storage<T, Allocator, GrowPolicy>& other) noexcept :
        vector_view{other.begin(), other.size()}
    {}

    template <typename Allocator, typename GrowPolicy>
    constexpr vector_view(vector_base<T, Allocator, GrowPolicy>& other) noexcept
        :
        vector_view{other.begin(), other.size()}
    {}

    constexpr vector_view(vector_view const& other) noexcept = default;

    constexpr vector_view& operator=(vector_view const& other) noexcept =
        default;

    // Move constructor.
    constexpr vector_view(vector_view&& other) noexcept = default;

    constexpr vector_view& operator=(vector_view&& other) noexcept = default;

    constexpr size_type size() const noexcept { return size_; }
    constexpr bool empty() const noexcept { return size_ == 0U; }
    constexpr iterator begin() noexcept { return buffer_; }
    constexpr const_iterator begin() const noexcept { return buffer_; }
    constexpr const_iterator cbegin() const noexcept { return buffer_; }
    constexpr iterator end() noexcept { return buffer_ + size_; }
    constexpr const_iterator end() const noexcept { return buffer_ + size_; }
    constexpr const_iterator cend() const noexcept { return buffer_ + size_; }

    constexpr pointer at(const size_type index) noexcept
    {
        return (buffer_ + index);
    }

    constexpr const_pointer at(const size_type index) const noexcept
    {
        return (buffer_ + index);
    }

    constexpr const_pointer cat(size_type const index) const noexcept
    {
        return (buffer_ + index);
    }

    constexpr reference operator[](size_type const index)
    {
        assert(index < size());
        return *at(index);
    }

    constexpr const_reference operator[](size_type const index) const
    {
        assert(index < size());
        return *at(index);
    }
};

}  // namespace htps

#endif
