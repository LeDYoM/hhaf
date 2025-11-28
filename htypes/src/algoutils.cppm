module;

#include <algorithm>
#include <initializer_list>

export module htypes:algoutils;

import :btypes;

namespace htps
{
template <typename Container, typename F>
void for_each_all(const Container& container, F&& function) noexcept
{
    std::for_each(std::begin(container), std::end(container),
                  htps::forward<F>(function));
}

template <typename Container, typename F>
void for_each_all(Container& container, F&& function) noexcept
{
    std::for_each(std::begin(container), std::end(container),
                  htps::forward<F>(function));
}

template <class T>
constexpr T min(std::initializer_list<T> values)
{
    return std::min(htps::move(values));
}

template <class T>
constexpr T max(std::initializer_list<T> values)
{
    return std::max(htps::move(values));
}

}  // namespace htps
