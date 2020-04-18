#pragma once

#ifndef HAF_LIBLOG_INCLUDE_HPP
#define HAF_LIBLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <mtypes/include/str.hpp>

namespace haf
{
using logClass = logger::Log<mtps::str, logger::COutCommiter>;
using DisplayLog = logger::LogDisplayer<logClass>;
using LogAsserter = logger::LogAsserter<DisplayLog>;

#ifdef NDEBUG
#define CLIENT_EXECUTE_IN_DEBUG(x) ((void)0)
#else
#define CLIENT_EXECUTE_IN_DEBUG(x) x
#endif

} // namespace haf

#endif
