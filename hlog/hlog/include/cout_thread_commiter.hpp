#pragma once

#ifndef LOGGER_LOG_COUT_THREAD_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_COUT_THREAD_COMMITER_INCLUDE_HPP

namespace haf
{

struct COutThreadCommiter
{
    static void init();

    static void finish();

    static void thread_func();

    static void commitlog(const char* const log_stream);
};

}  // namespace logger

#endif
