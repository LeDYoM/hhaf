#pragma warning(push)
#pragma warning(disable : 4668)

#include <hlog/include/hlog.hpp>

#include <logger/include/stream_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/thread_commiter.hpp>
#include <logger/include/null_commiter.hpp>

#pragma warning(pop)

namespace logger
{
template struct MixinCommiter<FileCommiter, COutCommiter>;
template struct Log<true, LogStream, ThreadFileCoutCommiter>;
template struct Log<true, LogStream, COutCommiter>;

template struct LogDisplayer<
    Log<true, LogStream, ThreadCommiter<FileCOutCommiter>>,
    SeverityType>;
template struct LogDisplayer<Log<true, LogStream, COutCommiter>, SeverityType>;

template struct LogAsserter<
    LogDisplayer<Log<true, LogStream, ThreadCommiter<FileCOutCommiter>>,
                 SeverityType>>;

template struct LogAsserter<
    LogDisplayer<Log<true, LogStream, COutCommiter>, SeverityType>>;

template struct LogInitializer<Log<true, LogStream, ThreadFileCoutCommiter>>;
template struct LogInitializer<Log<true, LogStream, COutCommiter>>;
}  // namespace logger
