#ifndef HAF_HLOG_INCLUDE_HPP
#define HAF_HLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/log_init.hpp>
#include <logger/include/thread_commiter.hpp>
#include <logger/include/mixin_commiter.hpp>
#include <logger/include/cout_commiter.hpp>
#include <logger/include/file_commiter.hpp>
#include <htypes/include/str.hpp>

namespace logger
{
class LogStream
{
    inline static htps::str data;

public:
    htps::str& operator()() { return data; }
};

using FileCOutCommiter       = MixinCommiter<FileCommiter, COutCommiter>;
using ThreadFileCoutCommiter = ThreadCommiter<FileCOutCommiter>;
// using CurrentCommiter = ThreadFileCoutCommiter;
using CurrentCommiter = COutCommiter;

using CurrentLog             = Log<true, LogStream, CurrentCommiter>;
using CurrentLogInitializer = LogInitializer<CurrentLog>;
using DisplayLog = LogDisplayer<CurrentLog, SeverityType, false>;
}  // namespace logger

namespace haf
{
    using LogAsserter = logger::LogAsserter<logger::DisplayLog>;
    using LogInitializer = logger::CurrentLogInitializer;
}
#endif
