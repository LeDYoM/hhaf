export module logger:mixin_commiter;

namespace logger
{
template <typename... Commiter>
struct MixinCommiter
{
    static inline void init() { (Commiter::init(), ...); }

    static inline void finish() { (Commiter::finish(), ...); }

    static inline void commitlog(char const* const log_stream)
    {
        (Commiter::commitlog(log_stream), ...);
    }
};

}  // namespace logger
