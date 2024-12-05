#ifndef LOGGER_LOG_NULL_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_NULL_COMMITER_INCLUDE_HPP

namespace logger
{
struct NullCommiter
{
    static inline void init() {}

    static inline void finish() {}

    static inline void commitlog(char const* const) {}
};

}  // namespace logger

#endif
