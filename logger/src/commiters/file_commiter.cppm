module;

#include <fstream>

export module logger:file_commiter;

namespace logger
{
std::ofstream* f{nullptr};

export struct FileCommiter
{
    static void init() { f = new std::ofstream("log.txt"); }

    static void finish()
    {
        (*f).flush();
        (*f).close();
        delete f;
        f = nullptr;
    }

    static void commitlog(const char* const log_stream)
    {
        (*f) << log_stream << std::endl;
    }
};

}  // namespace logger
