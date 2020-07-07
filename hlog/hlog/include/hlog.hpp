#pragma once

#ifndef HAF_HLOG_INCLUDE_HPP
#define HAF_HLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/log_init.hpp>
#include <logger/include/mixin_commiter.hpp>
#include <hlog/include/thread_commiter.hpp>

#include <mtypes/include/str.hpp>

namespace haf
{
using LogClass =
    logger::Log<true, mtps::str, logger::MixinCommiter<ThreadCommiter>>;
//extern template LogClass;

using DisplayLog = logger::LogDisplayer<LogClass, logger::SeverityType>;
//extern template DisplayLog;

using LogAsserter = logger::LogAsserter<DisplayLog>;
//extern template LogAsserter;

using LogInitializer = logger::LogInitializer<LogClass>;
//extern template LogInitializer;

}  // namespace haf

#endif
