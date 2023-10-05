#ifndef HLOG_FILE_COMMITER_INCLUDE_HPP
#define HLOG_FILE_COMMITER_INCLUDE_HPP

#include <logger/include/stream_commiter.hpp>

namespace logger
{
struct FileCommiter
{
    static void init();

    static void finish();

    static void commitlog(const char* const log_stream);
};

}  // namespace logger

#endif
