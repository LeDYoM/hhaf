#ifndef HLOG_THREAD_COMMITER_INCLUDE_HPP
#define HLOG_THREAD_COMMITER_INCLUDE_HPP

namespace logger
{
struct ThreadCommiterImpl
{
    static void init(void (*cmt_log)(const char* const log_stream));

    static void finish();

    static void commitlog(const char* const log_stream);
};

template <typename Commiter>
struct ThreadCommiter
{
    static void init()
    {
        Commiter::init();
        ThreadCommiterImpl::init(&Commiter::commitlog);
    }

    static void finish()
    {
        ThreadCommiterImpl::finish();
        Commiter::finish();
    }

    static void commitlog(const char* const log_stream)
    {
        ThreadCommiterImpl::commitlog(log_stream);
    }
};

}  // namespace logger

#endif
