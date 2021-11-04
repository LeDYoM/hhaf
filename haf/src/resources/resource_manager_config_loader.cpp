#include "resource_manager_config_loader.hpp"

#include "resources/resourcemanager.hpp"

#include <haf/include/filesystem/fileserializer.hpp>
#include <hlog/include/hlog.hpp>

#include "system/systemdatawrappercreator.hpp"

using namespace haf::types;

namespace haf::res
{

SetResourceConfigFileResult
ResourceManagerConfigLoader::parseResourceConfigFile(
    sys::DataWrapperCreator& data_wrapper_creator)
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    auto file_serializer{
        data_wrapper_creator.dataWrapper<sys::FileSerializer>()};
    auto const result{file_serializer->deserializeFromFile(
        resources_config_file_name_, resources_config_data_)};

    if (result != sys::FileSerializer::Result::Success)
    {
        if (result == sys::FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Resources file ", resources_config_file_name_,
                              " not found");
            return SetResourceConfigFileResult::FileNotFound;
        }
        else if (result == sys::FileSerializer::Result::ParsingError)
        {
            DisplayLog::error("File ", resources_config_file_name_,
                              " found but contains invalid format.");
            return SetResourceConfigFileResult::ParseError;
        }
        else
        {
            DisplayLog::error(
                "Unknow error reading and parsing simulation file: ",
                resources_config_file_name_);
            return SetResourceConfigFileResult::UnknownError;
        }
    }
    return SetResourceConfigFileResult::Ok;
}

void ResourceManagerConfigLoader::setResourcesDirectory(str const& directory)
{
    DisplayLog::debug("Set resources directory to: ", directory);
    config_directory_ = std::move(directory);
}

SetResourceConfigFileResult ResourceManagerConfigLoader::setResourceConfigFile(
    str const& file_name,
    sys::DataWrapperCreator& data_wrapper_creator)
{
    LogAsserter::log_assert(
        !file_name.empty(),
        "Trying to set an empty file name for resources file");

    if (file_name == resources_config_file_name_)
    {
        // It is ok to set the same resources file again.
        return SetResourceConfigFileResult::AlreadySet;
    }

    LogAsserter::log_assert(resources_config_file_name_.empty(),
                            "The resources file name was already set");

    resources_config_file_name_ = std::move(file_name);
    return parseResourceConfigFile(data_wrapper_creator);
}

namespace
{
static constexpr char TypeStr[] = "type";
static constexpr char FileStr[] = "file";
}  // namespace

bool ResourceManagerConfigLoader::loadSection(
    str const& section_name,
    sys::ResourceManager& resource_manager)
{
    bool global_result{true};

    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    // Fetch the section data.
    auto const resources_to_load_iterator{
        resources_config_data_.elements.cfind_checked(section_name)};

    if (resources_to_load_iterator.first)
    {
        // Load the section.
        for (auto const& resource_to_load :
             resources_to_load_iterator.second->second)
        {
            DisplayLog::debug("Going to load element: ", resource_to_load.name,
                              " of type ", resource_to_load.type,
                              " with file name: ", resource_to_load.file_name);

            str element_file{resource_to_load.file_name};
            if (!config_directory_.empty())
            {
                element_file = config_directory_ + element_file;
                DisplayLog::debug("Element file with directory: ",
                                  element_file);
            }

            bool local_result{false};

            if (resource_to_load.type == "ttf")
            {
                local_result = resource_manager.loadTTFont(
                    resource_to_load.name, element_file);
            }
            else if (resource_to_load.type == "texture")
            {
                local_result = resource_manager.loadTexture(
                    resource_to_load.name, element_file);
            }
            else if (resource_to_load.type.starts_with("bmp_font"))
            {
                local_result = resource_manager.loadBMPFont(
                    resource_to_load.name, element_file);
            }
            else
            {
                LogAsserter::log_assert(local_result,
                                        "Invalid type of element");
            }

            if (local_result)
            {
                DisplayLog::info("File ", element_file, " loaded as ",
                                 resource_to_load.name);
            }
            else
            {
                DisplayLog::error("File ", element_file, " cannot be loaded");
            }

            global_result &= local_result;
        }
    }

    return global_result;
}

}  // namespace haf::res
