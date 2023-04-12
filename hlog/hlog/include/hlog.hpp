#ifndef HAF_HLOG_INCLUDE_HPP
#define HAF_HLOG_INCLUDE_HPP

#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/log_init.hpp>
#include <hlog/include/thread_commiter.hpp>
#include <logger/include/mixin_commiter.hpp>
#include <htypes/include/str.hpp>
#include <hlog/include/cout_commiter.hpp>
#include <hlog/include/file_commiter.hpp>

namespace haf
{
class LogStream
{
    inline static htps::str data;

public:
    htps::str& operator()() { return data; }
};

}

namespace logger
{
extern template struct MixinCommiter<haf::FileCommiter, haf::COutCommiter>;
}

namespace haf
{
using FileCOutCommiter = logger::MixinCommiter<FileCommiter, COutCommiter>;

extern template struct ThreadCommiter<FileCOutCommiter>;
using ThreadFileCoutCommiter = ThreadCommiter<FileCOutCommiter>;

//using CurrentCommiter = ThreadFileCoutCommiter;
using CurrentCommiter = COutCommiter;

}

namespace logger
{
extern template struct LogDisplayer<
    Log<true, haf::LogStream, haf::CurrentCommiter>,
    SeverityType>;
}

namespace haf
{
using DisplayLog =
    logger::LogDisplayer<logger::Log<true, LogStream, CurrentCommiter>,
                         logger::SeverityType>;
}

namespace logger
{
extern template struct LogAsserter<haf::DisplayLog>;
}

namespace haf
{
using LogAsserter = logger::LogAsserter<DisplayLog>;
}

namespace logger
{
extern template struct LogInitializer<
    Log<true, haf::LogStream, haf::CurrentCommiter>>;
}

namespace haf
{
using LogInitializer =
    logger::LogInitializer<logger::Log<true, LogStream, CurrentCommiter>>;

}  // namespace haf

#endif
