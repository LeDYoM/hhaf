#include <hlog/include/hlog.hpp>

#include <logger/include/commiters/stream_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/commiters/thread_commiter.hpp>
#include <logger/include/commiters/null_commiter.hpp>

/*
namespace logger
{
template struct MixinCommiter<FileCommiter, COutCommiter>;
template struct Log<true, LogStream, ThreadFileCoutCommiter>;
template struct Log<true, LogStream, COutCommiter>;
template struct Log<false, LogStream, ThreadFileCoutCommiter>;
template struct Log<false, LogStream, COutCommiter>;

template struct LogDisplayer<Log<true, LogStream, ThreadFileCoutCommiter>,
                             SeverityType>;

template struct LogDisplayer<Log<true, LogStream, COutCommiter>, SeverityType>;

template struct LogDisplayer<Log<false, LogStream, ThreadFileCoutCommiter>,
                             SeverityType>;

template struct LogDisplayer<Log<false, LogStream, COutCommiter>, SeverityType>;


template struct LogAsserter<
    LogDisplayer<Log<true, LogStream, ThreadCommiter<FileCOutCommiter>>,
                 SeverityType>>;

template struct LogAsserter<
    LogDisplayer<Log<true, LogStream, COutCommiter>, SeverityType>>;

template struct LogInitializer<Log<true, LogStream, ThreadFileCoutCommiter>>;
template struct LogInitializer<Log<true, LogStream, COutCommiter>>;
}  // namespace logger
*/

static constexpr bool kDisplaySeverity{true};

template struct logger::CurrentLogInitializer;
template struct logger::
    LogDisplayer<logger::CurrentLog, logger::SeverityType, kDisplaySeverity>;
template struct logger::LogAsserter<DisplayLog>;
