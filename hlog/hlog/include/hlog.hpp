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

namespace logger
{
extern template class Log<true, mtps::str, MixinCommiter<haf::ThreadCommiter>>;
}
namespace haf
{

using LogClass =
    logger::Log<true, mtps::str, logger::MixinCommiter<ThreadCommiter>>;

}

namespace logger
{
extern template class LogDisplayer<haf::LogClass, SeverityType>;
}

namespace haf
{
using DisplayLog = logger::LogDisplayer<LogClass, logger::SeverityType>;
}

namespace logger
{
extern template class LogAsserter<haf::DisplayLog>;
}

namespace haf
{
using LogAsserter = logger::LogAsserter<DisplayLog>;
}

namespace logger
{
extern template class LogInitializer<haf::LogClass>;
}

namespace haf
{
using LogInitializer = logger::LogInitializer<LogClass>;
}  // namespace haf

#endif
