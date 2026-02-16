export module haf:core:log;

import hlog;
import :types;

template <typename... Args>
constexpr void  HAF_LOG_DEBUG([[maybe_unused]] Args&&... args) noexcept
{
    haf::DisplayLog::debug(core::move)
}

#define HAF_LOG_VERBOSE(...)  haf::DisplayLog::verbose(__VA_ARGS__)
#define HAF_LOG_INFO(...)  haf::DisplayLog::info(__VA_ARGS__)
#define HAF_ASSERT(...) haf::LogAsserter::log_assert(__VA_ARGS__)
