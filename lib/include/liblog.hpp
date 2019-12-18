#pragma once

#ifndef LIB_LIBLOG_INCLUDE_HPP
#define LIB_LIBLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <mtypes/include/str.hpp>

#include <cassert>

namespace lib
{
using logClass = logger::Log<str>;

template <typename... Args>
constexpr void log_info(Args &&... args) noexcept
{
    logClass::log<logClass::severity_type::info>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr void log_error(Args &&... args) noexcept
{
    logClass::log<logClass::severity_type::error>(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr void log_assert(const bool condition, Args &&... args) noexcept
{
    if (!condition)
    {
        log_error(std::forward<Args>(args)...);
    }
    assert(condition);
}

// Up to today in MSVC [[maybe_unused]] is ignored for
// variadic templates.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#endif
template <bool do_logs, typename... Args>
constexpr void log_info_if([[maybe_unused]] Args &&... args) noexcept
{
    if constexpr (do_logs)
    {
        log_info(std::forward<Args>(args)...);
    }
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef NDEBUG
#define CLIENT_EXECUTE_IN_DEBUG(x) ((void)0)
#else
#define CLIENT_EXECUTE_IN_DEBUG(x) x
#endif

} // namespace lib

#endif
