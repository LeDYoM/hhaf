#include "file_system.hpp"

#include <hlog/include/hlog.hpp>

#include <filesystem>
#include <string>
#include <fstream>

#include <htypes/include/object_utils.hpp>
#include <debug_utils/debug_system.hpp>
#include <system/get_system.hpp>
#include <haf/include/system/systemaccess.hpp>
#include <system/systemprovider.hpp>

using namespace htps;

namespace haf::sys
{
namespace
{
template <typename InnerType>
uptr<InnerType[]> readBuffer(uptr<InnerType[]> buffer,
                             const Path& file_name,
                             const size_type file_size)
{
    // Alias for the char type we are going to use to read the file
    using char_type = typename std::ifstream::char_type;

    // Check that the passed InnerType has the same size
    static_assert(sizeof(InnerType) == sizeof(char_type));

    {
        // Open the file to read in binary mode
        std::ifstream ifs(file_name.c_str(), std::ios::binary);
        // Get a pointer to the buffer but transforming the type to
        // the one we are going to read
        char_type* buffer_char = reinterpret_cast<char_type*>(buffer.get());

        // Read the buffer.
        ifs.read(buffer_char, file_size);
        ifs.close();
    }

    return buffer;
}
}  // namespace

bool FileSystem::processResult(IFileSerializer::Result const result,
                                   str const& pre_message,
                                   Path const& file,
                                   bool const assert_on_error)
{
    if (result != IFileSerializer::Result::Success)
    {
        if (result == IFileSerializer::Result::FileIOError)
        {
            DisplayLog::debug(pre_message, file, " not found");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " no found");
        }
        else if (result == IFileSerializer::Result::ParsingError)
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

RawMemory FileSystem::loadBinaryFile(const Path& file_name)
{
    if (fileExists(file_name))
    {
        // Note function returns size_max. size_type is maximum 4GB for a file.
        size_type file_size = static_cast<size_type>(
            std::filesystem::file_size(file_name.c_str()));

        uptr<std::byte[]> buf{muptr<std::byte[]>(file_size)};
        buf = readBuffer(std::move(buf), file_name, file_size);
        return RawMemory{std::move(buf), file_size};
    }
    return RawMemory{};
}

bool FileSystem::fileExists(const Path& path)
{
    return std::filesystem::exists(std::filesystem::path(path.c_str()));
}

str FileSystem::loadTextFile(const Path& file_name)
{
    if (fileExists(file_name))
    {
        // Note: function returns size_max. size_type is maximum 4GB for a file.
        size_type file_size = static_cast<size_type>(
            std::filesystem::file_size(file_name.c_str()));

        uptr<str::value_type[]> buf{muptr<str::value_type[]>(file_size + 1U)};
        buf = readBuffer(std::move(buf), file_name, file_size);

        buf[file_size] = static_cast<str::value_type>(0);
        return str(buf.get());
    }
    return str{};
}

bool FileSystem::saveTextFile(const Path& file_name, const str& data)
{
    // Open a file
    std::ofstream file(file_name.c_str());
    // Everything is correct by default
    bool correct{true};

    // If file open successfully
    if (file)
    {
        // Read the data
        file << data.c_str();
        // Correct is the status of the file object after reading it
        correct = file.good();
        file.close();
    }

    if (!file || !correct)
    {
        DisplayLog::error("Cannot write text file ", file_name);
    }

    return (file && correct);
}

IFileSerializer::Result FileSystem::deserializeFromFile(
    const Path& file_name,
    data::IDeserializable& data)
{
    auto& sp = systemProvider();
    SystemAccess ac(static_cast<ISystemProvider*>(&sp));
    debug::MemoryDataInitializer mdi{&getSystem<DebugSystem>(&ac)};
    str const text_data{loadTextFile(file_name)};
    if (!text_data.empty())
    {
        ObjectCompiler obj_compiler(text_data);
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

IFileSerializer::Result FileSystem::serializeToFile(
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

        return ((saveTextFile(file_name, std::move(data_str)))
                    ? Result::Success
                    : Result::FileIOError);
    }
    return Result::ParsingError;
}

}  // namespace haf::sys
