#ifndef HAF_LOG_LOG_ASSERTER_INCLUDE_HPP
#define HAF_LOG_LOG_ASSERTER_INCLUDE_HPP

#include "severity_type.hpp"
#include <source_location>
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
    template <typename T>
    static constexpr void log_assert(
        const bool condition,
        T&& arg,
        std::source_location const source = std::source_location::current())
    {
        // Store the condition in a variable to execute it only once.
        const bool cond{condition};

        if (!cond)
        {
            LogDisplayerClass::error("Assert!");
            LogDisplayerClass::error("File: ", source.file_name());
            LogDisplayerClass::error("Line and column: ", source.line(), ",",
                                     source.column());
            LogDisplayerClass::error("\t", source.function_name(), ": ",
                                     std::forward<T>(arg));
            if (UseLowLevelAssert)
            {
                assert(cond);
            }
        }
    }

    template <typename... Args>
    static constexpr void log_assert(const bool condition, Args&&... args)
    {
        // Store the condition in a variable to execute it only once.
        const bool cond{condition};

        if (!cond)
        {
            LogDisplayerClass::error(std::forward<Args>(args)...);
            if (UseLowLevelAssert)
            {
                assert(cond);
            }
        }
    }

    static bool UseLowLevelAssert;
};

template <typename LogDisplayerClass>
bool LogAsserter<LogDisplayerClass>::UseLowLevelAssert{true};

}  // namespace logger

#endif
