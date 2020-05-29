#include "fileserializer.hpp"
#include "filesystem.hpp"
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::sys
{
str FileSerializer::loadTextFile(const Path& file_name)
{
    return sys::getSystem<sys::FileSystem>(attachedNode())
        .loadTextFile(file_name);
}

bool FileSerializer::saveFile(const Path& file_name, const str& data)
{
    return sys::getSystem<sys::FileSystem>(attachedNode())
        .saveFile(file_name, data);
}

}  // namespace haf::sys