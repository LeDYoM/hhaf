HTPS_PRAGMA_ONCE
HTPS_PRAGMA_ONCE
#ifndef HTYPES_SPAN_INCLUDE_HPP
#define HTYPES_SPAN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector_base.hpp>
#include <cassert>
#include <type_traits>

namespace htps
{
template <typename T>
class span
{
public:
    static constexpr bool const is_const_v{std::is_const_v<T>};
    using iterator = rptr<T>;
    using const_iterator = rptr<T const>;
    using reference = T&;
    using const_reference = T const&;

    constexpr span(rptr<T> begin, rptr<T> end) noexcept :
        m_begin{begin}, m_end{end}
    {}

    template <size_type Size>
    constexpr span(T (&sp_data)[Size]) noexcept :
        m_begin{&sp_data[0U], sp_data + Size}
    {}

    constexpr size_type size() const noexcept
    {
        return static_cast<size_type>(m_end - m_begin);
    }

    constexpr bool empty() const noexcept { return m_begin == m_end; }

    constexpr iterator begin() noexcept { return m_begin; }
    constexpr const_iterator begin() const noexcept { return m_begin; }
    constexpr const_iterator cbegin() const noexcept { return m_begin; }
    constexpr iterator end() noexcept { return m_end; }
    constexpr const_iterator end() const noexcept { return m_end; }
    constexpr const_iterator cend() const noexcept { return m_end; }

    constexpr reference operator[](const size_type index)
    {
        assert(index < size());
        return *(m_begin + index);
    }

    constexpr const_reference operator[](const size_type index) const
    {
        assert(index < size());
        return *(m_begin + index);
    }

private:
    rptr<T> const m_begin;
    rptr<T> const m_end;
};

template <typename T>
constexpr auto make_span(T* begin, T* end) noexcept
{
    return span<T>{begin, end};
}

template <typename T, size_type Size>
constexpr auto make_span(T (&sp_data)[Size]) noexcept
{
    return span<T>{&sp_data[0U], sp_data + Size};
}

template <typename T,
          typename Allocator  = AllocatorType<T>,
          typename GrowPolicy = GrowPolicyUnary>
constexpr auto make_span(
    vector_base<T, Allocator, GrowPolicy> const& v) noexcept
{
    return make_span(v.begin(), v.end());
}

template <typename T,
          typename Allocator  = AllocatorType<T>,
          typename GrowPolicy = GrowPolicyUnary>
constexpr auto make_span(
    vector_base<T, Allocator, GrowPolicy>& v) noexcept
{
    return make_span(v.begin(), v.end());
}

template <typename T,
          typename Allocator  = AllocatorType<T>,
          typename GrowPolicy = GrowPolicyUnary>
constexpr auto make_const_span(
    vector_base<T, Allocator, GrowPolicy>& v) noexcept
{
    return make_span(v.cbegin(), v.cend());
}

}  // namespace htps

#endif
