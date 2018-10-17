#pragma once

#ifndef MTYPES_ALGO_UTILS_INCLUDE_HPP
#define MTYPES_ALGO_UTILS_INCLUDE_HPP

#include "vector.hpp"
#include "function.hpp"

namespace lib
{
    template <typename Container, typename Function>
    void for_each_safe(Container &container, Function function)
    {
        // Prepare a container of object functions
        vector<function<void()>> m_callbacks;

        for (auto element : container)
        {
            m_callbacks.emplace_back(f);
        }

        for (auto callback : m_callbacks)
        {
            callback();
        }
    }
}

#endif
