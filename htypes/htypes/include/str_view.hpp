HTPS_PRAGMA_ONCE
#ifndef MTPS_STR_VIEW_INCLUDE_HPP
#define MTPS_STR_VIEW_INCLUDE_HPP

#include "types.hpp"

namespace htps
{
namespace detail
{
template <typename char_type>
constexpr static size_type _str_len(char_type const* const p_str) noexcept
{
    if (!p_str)
    {
        return size_type{};
    }

    auto const* p_str_copy{p_str};

    while (*p_str_copy)
    {
        ++p_str_copy;
    }

    auto const tmp_result{p_str_copy - p_str};
    return ((tmp_result > 0U) ? static_cast<size_type>(tmp_result) : 0U);
}
}  // namespace detail

template <typename char_type>
class basic_str_view
{
public:
    using value_type = char_type;  //< Type of the characters used
    using const_reference =
        char_type const&;  //< Type of a const reference to a char_type;
    using const_iterator =
        char_type const*;  //< Const iterator type of the string

    constexpr basic_str_view() noexcept : begin_{nullptr}, size_{0U} {}

    constexpr basic_str_view(const_iterator const begin,
                             size_type const size) noexcept :
        begin_{begin}, size_{size}
    {}

    constexpr basic_str_view(const_iterator const begin,
                             const_iterator const end) noexcept :
        begin_{begin}, size_{static_cast<size_type>(end - begin)}
    {}

    template <size_type N>
    constexpr basic_str_view(char_type const (&data)[N]) noexcept :
        begin_{&data[0U]}, size_{N - 1}
    {}

    constexpr explicit basic_str_view(const_iterator const data) noexcept :
        basic_str_view{&data[0U], detail::_str_len(data)}
    {}

    [[nodiscard]] constexpr const_iterator data() const noexcept
    {
        return begin_;
    }
    [[nodiscard]] constexpr const_iterator begin() const noexcept
    {
        return begin_;
    }
    [[nodiscard]] constexpr const_iterator end() const noexcept
    {
        return begin_ + size_;
    }
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept
    {
        return begin();
    }
    [[nodiscard]] constexpr const_iterator cend() const noexcept
    {
        return end();
    }
    [[nodiscard]] constexpr char_type operator[](size_type const index)
    {
        return *(begin_ + index);
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return begin_ == nullptr || size_ == 0U || (size_ > 0U && *begin_ == 0);
    }

    [[nodiscard]] constexpr size_type size() const noexcept { return size_; }

    constexpr bool operator==(basic_str_view const& rhs) const noexcept
    {
        if (size() != rhs.size())
        {
            return false;
        }
        else
        {
            for (auto lhs_iterator{cbegin()}, rhs_iterator{rhs.cbegin()};
                 lhs_iterator != cend(); ++lhs_iterator, ++rhs_iterator)
            {
                if (!(*lhs_iterator == *rhs_iterator))
                {
                    return false;
                }
            }
            return true;
        }
    }

    constexpr bool operator==(char_type* const& rhs) const noexcept
    {
        return *this == basic_str_view{rhs};
    }

    template <size_type N>
    constexpr bool operator==(char_type const (&rhs)[N]) const noexcept
    {
        return *this == basic_str_view{rhs};
    }

    const_iterator begin_;
    size_type size_;
};

using str_view = basic_str_view<char>;

}  // namespace htps

#endif
