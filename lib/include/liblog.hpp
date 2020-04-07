#pragma once

#ifndef HAF_LIBLOG_INCLUDE_HPP
#define HAF_LIBLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <mtypes/include/str.hpp>

#include <cassert>

namespace haf
{
using logClass = logger::Log<mtps::str, logger::COutCommiter>;
using DisplayLog = logger::LogDisplayer<logClass>;

template <typename... Args>
constexpr void log_assert(const bool condition, Args &&... args) noexcept
{
    if (!condition)
    {
        DisplayLog::error(std::forward<Args>(args)...);
    }
    assert(condition);
}

// Up to today in MSVC [[maybe_unused]] is ignored for
// variadic templates.
//#ifdef _MSC_VER
//#pragma warning(push)
//#pragma warning(disable : 4100)
//#endif
//template <bool do_logs, typename... Args>
//constexpr void log_info_if([[maybe_unused]] Args &&... args) noexcept
//{
//    DisplayLog::log_if(do_logs, std::forward<Args>(args)...);
//}
//#ifdef _MSC_VER
//#pragma warning(pop)
//#endif

#ifdef NDEBUG
#define CLIENT_EXECUTE_IN_DEBUG(x) ((void)0)
#else
#define CLIENT_EXECUTE_IN_DEBUG(x) x
#endif

} // namespace haf

#endif
