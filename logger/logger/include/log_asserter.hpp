#pragma once

#ifndef HAF_LOG_LOG_ASSERTER_INCLUDE_HPP
#define HAF_LOG_LOG_ASSERTER_INCLUDE_HPP

#include "severity_type.hpp"
#include <cassert>

namespace logger
{

template <typename LogDisplayerClass>
struct LogAsserter
{
    template <typename... Args>
    constexpr void log_assert(const bool condition, Args&&... args) noexcept
    {
        // Store the condition in a variable to execute it only once.
        const bool cond{condition};

        if (!cond)
        {
            LogDisplayerClass::error(std::forward<Args>(args)...);
            assert(cond);
        }
    }
};

}  // namespace logger

#endif
