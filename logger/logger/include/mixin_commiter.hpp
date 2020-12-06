#ifndef LOGGER_LOG_MIXIN_COMMITER_INCLUDE_HPP
#define LOGGER_LOG_MIXIN_COMMITER_INCLUDE_HPP

namespace logger
{
template <typename... Commiter>
struct MixinCommiter
{
    static inline void init() { (Commiter::init(), ...); }

    static inline void finish() { (Commiter::finish(), ...); }

    static inline void commitlog(const char* const log_stream)
    {
        (Commiter::commitlog(log_stream), ...);
    }
};

}  // namespace logger

#endif
