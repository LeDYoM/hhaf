#ifndef LOGGER_LOG_COUT_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_COUT_COMMITER_INCLUDE_HPP

namespace logger
{
template <auto Stream>
struct StreamCommiter
{
    static void init() {}

    static void finish() {}

    static inline void commitlog(const char* const log_stream)
    {
        (*Stream) << log_stream << "\n";
        (*Stream).flush();
    }
};

}  // namespace logger

#endif
