HAF_PRAGMA_ONCE
#ifndef HAF_LOG_ASSERT_INCLUDE_HPP
#define HAF_LOG_ASSERT_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#ifdef __cpp_lib_source_location
#include <source_location>
#endif

namespace haf
{
using LogAsserter = logger::LogAsserter<DisplayLog>;
}

namespace haf::log
{
template <typename T>
constexpr void log_assert(
    const bool condition,
    T&& arg
#ifdef __cpp_lib_source_location
    ,
    std::source_location const source = std::source_location::current()
#endif
)
{
    LogAsserter::log_assert(condition, core::forward<T>(arg)
#ifdef __cpp_lib_source_location
                                           ,
                            source
#endif
    );

    template <typename... Args>
    constexpr void log_assert(const bool condition, Args&&... args)
    {
        LogAsserter::log_assert(condition, core::forward<Args>(args)...);
    }
}
}  // namespace haf::log

#define LOG_ASSERT(...) log::log_assert();

#endif
