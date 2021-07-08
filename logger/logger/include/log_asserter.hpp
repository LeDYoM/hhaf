#ifndef HAF_LOG_LOG_ASSERTER_INCLUDE_HPP
#define HAF_LOG_LOG_ASSERTER_INCLUDE_HPP

#include "severity_type.hpp"
#include <cassert>

namespace logger
{

/**
 * @brief Class to perform run-time assertions in code.
 * Provides constexpr methods that could be eliminated under certain conditions.
 * @tparam LogDisplayerClass Class that performs the actual logging.
 */
template <typename LogDisplayerClass>
struct LogAsserter
{
    template <typename... Args>
    static constexpr void log_assert(const bool condition,
                                     Args&&... args) noexcept
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
