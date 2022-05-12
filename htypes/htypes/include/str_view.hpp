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
    constexpr basic_str_view(char_type const* const begin,
                       size_type const size) :
        begin_{begin}, size_{size}
    {}

    template <size_type N>
    constexpr basic_str_view(char const (&data)[N]) : begin_{&data[0U]}, size_{N}
    {}

    constexpr basic_str_view(char const* data) : begin_{&data[0U]}, size_{detail::_str_len(data)} {}

    constexpr char_type const* data() const noexcept { return begin_; }

    char_type const* begin_;
    size_type const size_;
};

using str_view = basic_str_view<char>;

}  // namespace htps

#endif
