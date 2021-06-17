#include <hlog/include/hlog.hpp>

#include <logger/include/stream_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <hlog/include/thread_commiter.hpp>

#include <htypes/include/str.hpp>

namespace logger
{
template struct Log<true, htps::str, MixinCommiter<haf::ThreadCommiter>>;
template struct LogDisplayer<haf::LogClass, SeverityType>;
template struct LogAsserter<haf::DisplayLog>;
template struct LogInitializer<haf::LogClass>;
}  // namespace logger

namespace haf
{}  // namespace haf
