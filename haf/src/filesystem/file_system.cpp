#include "file_system.hpp"
#include "file_system_private_funcs.hpp"
#include <hlog/include/hlog.hpp>

#include <debug_system/debug_system.hpp>
#include <system/get_system.hpp>
#include <haf/include/system/system_access.hpp>
#include <system/system_provider.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/data/types.hpp>

using namespace haf::core;

namespace haf::sys
{
bool FileSystem::processResult(IFileSerializer::Result const result,
                               str const& pre_message,
                               Path const& file,
                               bool const assert_on_error)
{
    if (result != IFileSerializer::Result::Success)
    {
        if (result == IFileSerializer::Result::FileIOError)
        {
            logger::DisplayLog::debug(pre_message, file, " not found");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " not found");
        }
        else if (result == IFileSerializer::Result::ParsingError)
        {
            logger::DisplayLog::debug(pre_message, file,
                                      " found, but contains invalid format");
            LogAsserter::log_assert(!assert_on_error, pre_message, file,
                                    " found, but contains invalid format");
        }
        else
        {
            logger::DisplayLog::debug(pre_message, file,
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
        auto const file_size{detail::fileSize(file_name)};

        vector<char> buf(file_size);
        buf = detail::readBuffer(htps::move(buf), file_name, file_size);
        return RawMemory{htps::move(buf)};
    }
    return RawMemory{};
}

bool FileSystem::fileExists(Path const& path)
{
    return detail::fileExists(path);
}

str FileSystem::loadTextFile(const Path& file_name)
{
    return RawMemory{loadBinaryFile(file_name)}.to_str();
}

bool FileSystem::saveTextFile(const Path& file_name, const str& data)
{
    // Open a file
    std::ofstream file{file_name.c_str()};
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
        logger::DisplayLog::error("Cannot write text file ", file_name);
    }

    return (file && correct);
}

IFileSerializer::Result FileSystem::deserializeFromFile(
    const Path& file_name,
    data::IDeserializable& data)
{
    str const text_data{loadTextFile(file_name)};
    if (!text_data.empty())
    {
        data::TextSerializer text_serializer;
        return (text_serializer.deserializeFromText(text_data, data)
                    ? Result::Success
                    : Result::ParsingError);
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
    str data_str;
    data::TextSerializer text_serializer;

    auto const result{text_serializer.serializeToText(data_str, data)};

    if (result)
    {
        return ((saveTextFile(file_name, htps::move(data_str)))
                    ? Result::Success
                    : Result::FileIOError);
    }
    return Result::ParsingError;
}

}  // namespace haf::sys
