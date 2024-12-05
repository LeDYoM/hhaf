#include "resource_manager_config_loader.hpp"

#include "resources/resource_manager.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/resources/resource_descriptor.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace logger;

namespace haf::res
{

SetResourceConfigFileResult
ResourceManagerConfigLoader::parseResourceConfigFile(
    sys::SubSystemViewer sub_system_viewer)
{
    LogAsserter::log_assert(!resources_config_file_name_.empty(),
                            "The resources file name was not set");

    auto file_serializer{sub_system_viewer.subSystem<sys::IFileSerializer>()};
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

    resources_config_file_name_ = htps::move(file_name);
    return parseResourceConfigFile(htps::move(sub_system_viewer));
}

bool ResourceManagerConfigLoader::loadSection(str const& section_name,
                                              IResourceLoader& resource_loader)
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
            ResourceDescriptor resource_descriptor{
                resource_to_load.first, resource_to_load.second.type,
                resource_to_load.second.file_name};

            DisplayLog::debug(
                "Going to load element: ", resource_descriptor.name,
                " of type ", resource_descriptor.type,
                " with file name: ", resource_descriptor.fileName);

            if (!config_directory_.empty())
            {
                resource_descriptor.fileName =
                    config_directory_ + resource_descriptor.fileName;
                DisplayLog::debug("Element file with directory: ",
                                  resource_descriptor.fileName);
            }

            bool const local_result{
                resource_loader.loadResource(resource_descriptor)};

            if (local_result)
            {
                DisplayLog::info("File ", resource_descriptor.fileName,
                                 " loaded as ", resource_descriptor.name);
            }
            else
            {
                DisplayLog::error("File ", resource_descriptor.fileName,
                                  " cannot be loaded as ",
                                  resource_descriptor.name);
            }

            global_result &= local_result;
        }
    }

    return global_result;
}

}  // namespace haf::res
