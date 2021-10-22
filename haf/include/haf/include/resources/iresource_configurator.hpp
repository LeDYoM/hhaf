#ifndef HAF_RESOURCES_RESOURCES_CONFIGURATOR_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIGURATOR_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::res
{
/**
 * @brief Enum to return the status of the function @b setResourceConfigFile
 */
enum class SetResourceConfigFileResult : types::u8
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
class IResourcesConfigurator
{
public:
    /**
     * @brief Set the directory where the resources will be loaded.
     * @param[in] directory The directory where the resources are
     */
    virtual void setResourcesDirectory(types::str const& directory) = 0;

    /**
     * @brief Set the config file to be loaded
     * @param[in] fileName Name of the configuration file
     * @return Result status of the function
     * @see SetResourceConfigFileResult
     */
    virtual SetResourceConfigFileResult setResourceConfigFile(types::str const& fileName) = 0;

    /**
     * @brief Load a section from the previously set config file for resource
     * loading.
     *
     * @return true Section loaded correctly
     * @return false Section not loaded
     */
    virtual bool loadSection(htps::str const& section) = 0;
};

}  // namespace haf::res

#endif
