#include <haf/include/filesystem/fileserializer.hpp>
#include <filesystem/filesystem.hpp>
#include <system/systemprovider.hpp>
#include <system/get_system.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
bool FileSerializer::processResult(Result const result,
                                   str const& pre_message,
                                   Path const& file,
                                   bool const assert_on_error)
{
    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug(pre_message, file, " not found");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " no found");
        }
        else if (result == FileSerializer::Result::ParsingError)
        {
            DisplayLog::debug(pre_message, file,
                              " found, but contains invalid format");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " found, but contains invalid format");
        }
        else
        {
            DisplayLog::debug(pre_message, file,
                              " : Unknown error trying to read file");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " : Unknown error trying to read file");
        }
        return false;
    }

    return true;
}

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
    data::IDeserializable& data)
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
    const data::ISerializable& data)
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
