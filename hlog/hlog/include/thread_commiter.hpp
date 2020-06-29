#pragma once

#ifndef HLOG_THREAD_COMMITER_INCLUDE_HPP
#define HLOG_THREAD_COMMITER_INCLUDE_HPP

namespace haf
{

struct ThreadCommiter
{
    static void init();

    static void finish();

    static void thread_func();

    static void commitlog(const char* const log_stream);
};

}  // namespace logger

#endif
