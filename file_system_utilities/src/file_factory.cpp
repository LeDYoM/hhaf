#include "file_factory.hpp"
#include <fsu/include/ifile_driver.hpp>

#include <htypes/include/vector.hpp>

#include "driver_normal/in_file_normal.hpp"

using namespace htps;

namespace fsu
{
struct FileFactory::FileFactoryPrivate
{
    vector<uptr<IFileDriver>> m_file_managers;
};

FileFactory::FileFactory() : m_p{htps::make_pimplp<FileFactoryPrivate>()}
{}

FileFactory::~FileFactory() = default;

bool FileFactory::addDriver(htps::uptr<IFileDriver> ifile_manager)
{
    m_p->m_file_managers.push_back(htps::move(ifile_manager));
    return true;
}

uptr<IInFile> FileFactory::inFile(str const& file_name)
{
    for (auto&& file_manager : m_p->m_file_managers)
    {
        if (auto file{file_manager->openForRead(file_name)}; file != nullptr)
        {
            return file;
        }
    }
    return nullptr;
}

}  // namespace fsu
