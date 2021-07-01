#ifndef HAF_RESOURCES_RESOURCES_CONFIGURATOR_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIGURATOR_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/system/idatawrapper.hpp>

namespace haf::res
{
/**
 * @brief Enum to return the status of the function @b setResourceConfigFile
 */
enum class SetResourceConfigFileResult : htps::u8
{
    Ok = 0U,       ///< Everything was ok
    AlreadySet,    ///< The same file was already set. No actions performed
    FileNotFound,  ///< The file was not found or no permission to open it
    ParseError,    ///< Error parsing the file
    UnknownError   /// Unknown error reading the file
};

/**
 * @brief Class to perform the load of resources using sections.
 */
class ResourcesConfigurator : public sys::IDataWrapper
{
public:
    /**
     * @brief Set the directory where the resources will be loaded.
     * @param[in] directory The directory where the resources are
     */
    void setResourcesDirectory(htps::str directory);

    /**
     * @brief Set the config file to be loaded
     * @param[in] fileName Name of the configuration file
     * @return Result status of the function
     * @see SetResourceConfigFileResult
     */
    SetResourceConfigFileResult setResourceConfigFile(htps::str fileName);

    /**
     * @brief Load a section from the previously set config file for resource
     * loading.
     *
     * @return true Section loaded correctly
     * @return false Section not loaded
     */
    bool loadSection(htps::str const&);
};

}  // namespace haf::res

#endif
