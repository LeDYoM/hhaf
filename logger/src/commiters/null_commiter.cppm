export module logger:null_commiter;

namespace logger
{
struct NullCommiter
{
    static inline void init() {}

    static inline void finish() {}

    static inline void commitlog(char const* const) {}
};

}  // namespace logger
