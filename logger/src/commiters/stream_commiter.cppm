export module logger:stream_commiter;

namespace logger
{
export template <auto Stream>
struct StreamCommiter
{
    static void init() {}

    static void finish() {}

    static void commitlog(const char* const log_stream)
    {
        (*Stream) << log_stream << "\n";
        (*Stream).flush();
    }
};

}  // namespace logger
