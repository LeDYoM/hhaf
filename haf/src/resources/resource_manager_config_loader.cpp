#include "resource_manager_config_loader.hpp"

#include "resources/resourcemanager.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/system/subsystem_view.hpp>

#include <hlog/include/hlog.hpp>

using namespace haf::types;

namespace haf::res
{

SetResourceConfigFileResult
ResourceManagerConfigLoader::parseResourceConfigFile(
    sys::SubSystemViewer sub_system_viewer)
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    auto file_serializer{
        sub_system_viewer.subSystem<sys::IFileSerializer>()};
    auto const result{file_serializer->deserializeFromFile(
        resources_config_file_name_, resources_config_data_)};

    if (result != sys::IFileSerializer::Result::Success)
    {
        if (result == sys::IFileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Resources file ", resources_config_file_name_,
                              " not found");
            return SetResourceConfigFileResult::FileNotFound;
        }
        else if (result == sys::IFileSerializer::Result::ParsingError)
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
    config_directory_ = directory;
}

SetResourceConfigFileResult ResourceManagerConfigLoader::setResourceConfigFile(
    str const& file_name,
    sys::SubSystemViewer sub_system_viewer)
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
    return parseResourceConfigFile(std::move(sub_system_viewer));
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
        resources_config_data_.elements().cfind_checked(section_name)};

    if (resources_to_load_iterator.first)
    {
        // Load the section.
        for (auto const& resource_to_load :
             resources_to_load_iterator.second->second.elements())
        {
            auto const& name{resource_to_load.first};
            auto const& type{resource_to_load.second.type};
            auto element_file{resource_to_load.second.file_name};

            DisplayLog::debug("Going to load element: ", name, " of type ",
                              type, " with file name: ", element_file);

            if (!config_directory_.empty())
            {
                element_file = config_directory_ + element_file;
                DisplayLog::debug("Element file with directory: ",
                                  element_file);
            }

            bool local_result{false};

            if (type == "ttf")
            {
                local_result = resource_manager.loadTTFont(name, element_file);
            }
            else if (type == "texture")
            {
                local_result = resource_manager.loadTexture(name, element_file);
            }
            else if (type.starts_with("bmp_font"))
            {
                local_result = resource_manager.loadBMPFont(name, element_file);
            }
            else
            {
                LogAsserter::log_assert(local_result,
                                        "Invalid type of element");
            }

            if (local_result)
            {
                DisplayLog::info("File ", element_file, " loaded as ", name);
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
