#ifndef HAF_CORE_LOG_INCLUDE_HPP
#define HAF_CORE_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

#define HAF_LOG_DEBUG(...)  haf::DisplayLog::debug(__VA_ARGS__)
#define HAF_LOG_VERBOSE(...)  haf::DisplayLog::verbose(__VA_ARGS__)
#define HAF_LOG_INFO(...)  haf::DisplayLog::info(__VA_ARGS__)
#define HAF_ASSERT(...) haf::LogAsserter::log_assert(__VA_ARGS__)

#endif
