#include "resourcemanager.hpp"

using namespace haf::types;

namespace haf::res
{

SetResourceConfigFileResult ResourceManager::parseResourceConfigFile()
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    SystemDataWrapperCreator dwc{*this};
    auto file_serializer = dwc.dataWrapper<FileSerializer>();
    auto const result    = file_serializer->deserializeFromFile(
        resources_config_file_name_, resources_config_data_);

    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Resources file ", resources_config_file_name_,
                              " not found");
            return SetResourceConfigFileResult::FileNotFound;
        }
        else if (result == FileSerializer::Result::ParsingError)
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

void ResourceManager::setResourcesDirectory(str const& directory)
{
    DisplayLog::debug("Set resources directory to: ", directory);
    p_->config_directory_ = std::move(directory);
}

SetResourceConfigFileResult ResourceManager::setResourceConfigFile(
    str const& file_name)
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
    return parseResourceConfigFile();
}

namespace
{
static constexpr char TypeStr[] = "type";
static constexpr char FileStr[] = "file";
}  // namespace

bool ResourceManager::loadSection(str const& section_name)
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
            if (!p_->config_directory_.empty())
            {
                element_file = p_->config_directory_ + element_file;
                DisplayLog::debug("Element file with directory: ",
                                  element_file);
            }

            bool local_result{false};

            if (resource_to_load.type == "ttf")
            {
                local_result = loadTTFont(resource_to_load.name, element_file);
            }
            else if (resource_to_load.type == "texture")
            {
                local_result = loadTexture(resource_to_load.name, element_file);
            }
            else if (resource_to_load.type.starts_with("bmp_font"))
            {
                local_result = loadBMPFont(resource_to_load.name, element_file);
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

}  // namespace haf::sys
