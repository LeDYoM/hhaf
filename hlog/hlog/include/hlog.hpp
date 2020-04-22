#pragma once

#ifndef HAF_LIBLOG_INCLUDE_HPP
#define HAF_LIBLOG_INCLUDE_HPP

#include <logger/include/cout_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>

#include <mtypes/include/str.hpp>

namespace haf
{
using LogClass = logger::Log<true, mtps::str, logger::COutCommiter>;
using DisplayLog = logger::LogDisplayer<LogClass>;
using LogAsserter = logger::LogAsserter<DisplayLog>;

} // namespace haf

#endif
