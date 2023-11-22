HAF_PRAGMA_ONCE
#ifndef HAF_LOG_LOG_INCLUDE_HPP
#define HAF_LOG_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <haf/include/core/types.hpp>

namespace haf::log
{
using LogDisplayer = logger::DisplayLog;
}  // namespace haf::log

namespace haf::log
{
template <typename... Args>
constexpr void debug(Args&&... args) noexcept
{
    LogDisplayer::debug(core::forward<Args>(args)...);
}

template <bool Condition, typename... Args>
static constexpr void debug_if_ce(Args&&... args) noexcept
{
    LogDisplayer::debug_if_ce<Condition>(core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void debug_if(bool const cond, Args&&... args) noexcept
{
    LogDisplayer::debug_if(cond, core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void info(Args&&... args) noexcept
{
    LogDisplayer::info(core::forward<Args>(args)...);
}

template <bool Condition, typename... Args>
static constexpr void info_if_ce([[maybe_unused]] Args&&... args) noexcept
{
    LogDisplayer::info_if_ce<Condition>(core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void info_if(bool const cond, Args&&... args) noexcept
{
    LogDisplayer::info_if(cond, core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void warn(Args&&... args) noexcept
{
    LogDisplayer::warn(core::forward<Args>(args)...);
}

template <bool Condition, typename... Args>
static constexpr void warn_if_ce([[maybe_unused]] Args&&... args) noexcept
{
    LogDisplayer::warn_if_ce<Condition>(core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void warn_if(bool const cond, Args&&... args) noexcept
{
    LogDisplayer::warn_if(cond, core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void error(Args&&... args) noexcept
{
    LogDisplayer::error(core::forward<Args>(args)...);
}

template <bool Condition, typename... Args>
static constexpr void error_if_ce(Args&&... args) noexcept
{
    LogDisplayer::error_if_ce<Condition>(core::forward<Args>(args)...);
}

template <typename... Args>
static constexpr void error_if(bool const cond, Args&&... args) noexcept
{
    LogDisplayer::error_if(cond, core::forward<Args>(args)...);
}

}  // namespace haf::log
#define LOG_DEBUG(...) log::debug(__VA_ARGS__)
#define LOG_DEBUG_IF(cond, ...) log::debug_if(cond, __VA_ARGS__)
#define LOG_DEBUG_IF_CE(cond, ...) log::debug_if_ce<cond>(__VA_ARGS__)

#define LOG_INFO(...) log::info(__VA_ARGS__)
#define LOG_INFO_IF(cond, ...) log::info_if(cond, __VA_ARGS__)
#define LOG_INFO_IF_CE(cond, ...) log::info_if_ce<cond>(__VA_ARGS__)

#define LOG_WARN(...) log::warn(__VA_ARGS__)
#define LOG_WARN_IF(cond, ...) log::warn_if(cond, __VA_ARGS__)
#define LOG_WARN_IF_CE(cond, ...) log::warn_if_ce<cond>(__VA_ARGS__)

#define LOG_ERROR(...) log::error(__VA_ARGS__)
#define LOG_ERROR_IF(cond, ...) log::error_if(cond, __VA_ARGS__)
#define LOG_ERROR_IF_CE(cond, ...) log::error_if_ce<cond>(__VA_ARGS__)

#endif
