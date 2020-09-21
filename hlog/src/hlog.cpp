#include <hlog/include/hlog.hpp>

#include <logger/include/stream_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <hlog/include/thread_commiter.hpp>

#include <mtypes/include/str.hpp>

namespace logger
{
    template class Log<true, mtps::str, MixinCommiter<haf::ThreadCommiter>>;
    template class LogDisplayer<haf::LogClass, SeverityType>;
    template class LogAsserter<haf::DisplayLog>;
    template class LogInitializer<haf::LogClass>;
}

namespace haf
{

} // namespace haf
