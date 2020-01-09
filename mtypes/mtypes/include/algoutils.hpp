#pragma once

#ifndef MTYPES_ALGO_UTILS_INCLUDE_HPP
#define MTYPES_ALGO_UTILS_INCLUDE_HPP

#include <algorithm>

namespace lib
{
    template <typename Container, typename F>
    void for_each_all(const Container &container, F&& function) noexcept
    {
        std::for_each(
            std::begin(container), 
            std::end(container), 
            std::forward<F>(function));
    }
}

#endif
