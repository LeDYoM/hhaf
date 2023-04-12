#pragma warning(push)
#pragma warning(disable : 4668)

#include <hlog/include/hlog.hpp>

#include <logger/include/stream_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <hlog/include/thread_commiter.hpp>
#include <logger/include/null_commiter.hpp>

#pragma warning(pop)

namespace logger
{
template struct MixinCommiter<haf::FileCommiter, haf::COutCommiter>;
}

namespace haf
{
template struct ThreadCommiter<FileCOutCommiter>;

}  // namespace haf

namespace logger
{
template struct Log<true, haf::LogStream, haf::ThreadFileCoutCommiter>;
template struct Log<true, haf::LogStream, haf::COutCommiter>;

template struct LogDisplayer<
    Log<true, haf::LogStream, haf::ThreadCommiter<haf::FileCOutCommiter>>,
    SeverityType>;
template struct LogDisplayer<Log<true, haf::LogStream, haf::COutCommiter>,
                             SeverityType>;

template struct LogAsserter<LogDisplayer<
    Log<true, haf::LogStream, haf::ThreadCommiter<haf::FileCOutCommiter>>,
    SeverityType>>;

template struct LogAsserter<
    LogDisplayer<Log<true, haf::LogStream, haf::COutCommiter>, SeverityType>>;

template struct LogInitializer<
    Log<true, haf::LogStream, haf::ThreadFileCoutCommiter>>;
template struct LogInitializer<
    Log<true, haf::LogStream, haf::COutCommiter>>;
}  // namespace logger
