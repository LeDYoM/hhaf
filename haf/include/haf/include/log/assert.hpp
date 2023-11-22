HAF_PRAGMA_ONCE
#ifndef HAF_LOG_ASSERT_INCLUDE_HPP
#define HAF_LOG_ASSERT_INCLUDE_HPP

#include <logger/include/log_asserter.hpp>
#include <haf/include/log/log.hpp>

namespace haf::log
{
template <typename... Args>
constexpr void log_assert(const bool condition, Args&&... args)
{
    logger::LogAsserter<LogDisplayer>::log_assert(condition,
                                                  core::forward<Args>(args)...);
}
}  // namespace haf::log

#define LOG_ASSERT(c, ...) log::log_assert(c, __VA_ARGS__);

#endif
