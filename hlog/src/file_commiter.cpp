#include <hlog/include/file_commiter.hpp>

#pragma warning(push)
#pragma warning(disable : 4668)

#include <fstream>

#pragma warning(pop)

namespace logger
{
std::ofstream* f{nullptr};

void FileCommiter::init()
{
    f = new std::ofstream("log.txt");
}

void FileCommiter::finish()
{
    (*f).flush();
    (*f).close();
    delete f;
    f = nullptr;
}

void FileCommiter::commitlog(const char* const log_stream)
{
    (*f) << log_stream << std::endl;
}

}  // namespace logger
