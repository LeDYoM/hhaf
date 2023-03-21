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

extern template struct logger::MixinCommiter<FileCommiter, COutCommiter>;
using FileCOutCommiter = logger::MixinCommiter<FileCommiter, COutCommiter>;

extern template struct ThreadCommiter<FileCOutCommiter>;
using ThreadFileCoutCommiter = ThreadCommiter<FileCOutCommiter>;

//using CurrentCommiter = ThreadFileCoutCommiter;
using CurrentCommiter = COutCommiter;

extern template struct logger::LogDisplayer<
    logger::Log<true, LogStream, CurrentCommiter>,
    logger::SeverityType>;

using DisplayLog =
    logger::LogDisplayer<logger::Log<true, LogStream, CurrentCommiter>,
                         logger::SeverityType>;

extern template struct logger::LogAsserter<DisplayLog>;
using LogAsserter = logger::LogAsserter<DisplayLog>;

extern template struct logger::LogInitializer<
    logger::Log<true, LogStream, CurrentCommiter>>;
using LogInitializer =
    logger::LogInitializer<logger::Log<true, LogStream, CurrentCommiter>>;

}  // namespace haf

#endif
