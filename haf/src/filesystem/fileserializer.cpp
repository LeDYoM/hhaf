#include <haf/include/filesystem/fileserializer.hpp>
#include <filesystem/filesystem.hpp>
#include <system/systemprovider.hpp>
#include <system/get_system.hpp>

using namespace htps;

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

FileSerializer::Result FileSerializer::deserializeFromFile(
    const Path& file_name,
    shdata::IShareable& data)
{
    const htps::str text_data{loadTextFile(file_name)};
    if (!text_data.empty())
    {
        htps::ObjectCompiler obj_compiler(text_data);
        if (obj_compiler.compile())
        {
            // The compilation was correct so, at least we
            // have a valid Object.
            return ((data.deserialize(obj_compiler.result()))
                        ? Result::Success
                        : Result::ParsingError);
        }
        else
        {
            return Result::ParsingError;
        }
    }
    else
    {
        return Result::FileIOError;
    }
}

FileSerializer::Result FileSerializer::serializeToFile(
    const Path& file_name,
    const shdata::IShareable& data)
{
    //        auto temp{htps::Serializer<T>::serialize(data)};
    htps::Object obj;
    auto temp(data.serialize(obj));

    if (temp)
    {
        htps::str data_str;
        data_str << obj;

        return ((saveFile(file_name, std::move(data_str)))
                    ? Result::Success
                    : Result::FileIOError);
    }
    return Result::ParsingError;
}

}  // namespace haf::sys
