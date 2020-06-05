#pragma once

#ifndef HAF_HLOG_INCLUDE_HPP
#define HAF_HLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/log_init.hpp>
#include <hlog/include/cout_thread_commiter.hpp>

#include <mtypes/include/str.hpp>

namespace haf
{
extern template logger::Log<true, mtps::str, COutThreadCommiter>;
using LogClass = logger::Log<true, mtps::str, COutThreadCommiter>;

extern template logger::LogDisplayer<LogClass, logger::SeverityType>;
using DisplayLog = logger::LogDisplayer<LogClass, logger::SeverityType>;

extern template logger::LogAsserter<DisplayLog>;
using LogAsserter = logger::LogAsserter<DisplayLog>;

extern template logger::LogInitializer<LogClass>;
using LogInitializer = logger::LogInitializer<LogClass>;

} // namespace haf

#endif
