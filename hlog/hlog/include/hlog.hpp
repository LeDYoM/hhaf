#pragma once

#ifndef HAF_LIBLOG_INCLUDE_HPP
#define HAF_LIBLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <hlog/include/cout_thread_commiter.hpp>

#include <mtypes/include/str.hpp>

namespace haf
{
using LogClass = logger::Log<true, mtps::str, COutThreadCommiter>;
using DisplayLog = logger::LogDisplayer<LogClass, logger::SeverityType>;
using LogAsserter = logger::LogAsserter<DisplayLog>;

} // namespace haf

#endif
