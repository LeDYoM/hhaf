#include <hlog/include/file_commiter.hpp>

#include <iostream>
#include <fstream>

namespace haf
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

}  // namespace haf
