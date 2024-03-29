#ifndef HAF_LOG_LOG_ASSERTER_INCLUDE_HPP
#define HAF_LOG_LOG_ASSERTER_INCLUDE_HPP

#include "severity_type.hpp"
#include <cassert>

#ifdef __cpp_lib_source_location
    #include <source_location>
#endif

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
        T&& arg
#ifdef __cpp_lib_source_location
        , std::source_location const source = std::source_location::current()
#endif
)
    {
        // Store the condition in a variable to execute it only once.
        const bool cond{condition};

        if (!cond)
        {
            LogDisplayerClass::error("Assert!");
#ifdef __cpp_lib_source_location
            LogDisplayerClass::error("File: ", source.file_name());
            LogDisplayerClass::error("Line and column: ", source.line(), ",",
                                     source.column());
#endif
            LogDisplayerClass::error(
#ifdef __cpp_lib_source_location
                "\t", source.function_name(), ": ",
#endif
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
