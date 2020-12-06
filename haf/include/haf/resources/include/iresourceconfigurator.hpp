#ifndef HAF_RESOURCES_IRESOURCESCONFIGURATOR_INCLUDE_HPP
#define HAF_RESOURCES_IRESOURCESCONFIGURATOR_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::res
{
/**
 * @brief Enum to return the status of the function @b setResourceConfigFile
 */
enum class SetResourceConfigFileResult : mtps::u8
{
    Ok = 0U,       ///< Everything was ok
    AlreadySet,    ///< The same file was already set. No actions performed
    FileNotFound,  ///< The file was not found or no permission to open it
    ParseError,    ///< Error parsing the file
    UnknownError   /// Unknown error reading the file
};

/**
 * @brief Interface class to perform the load of resources using sections.
 */
class IResourcesConfigurator
{
public:
    /**
     * @brief Set the config file to be loaded
     *
     * @return Result status of the function
     * @see SetResourceConfigFileResult
     */
    virtual SetResourceConfigFileResult setResourceConfigFile(mtps::str) = 0;

    /**
     * @brief Load a section from the previously set config file for resource
     * loading.
     * 
     * @return true Section loaded correctly
     * @return false Section not loaded
     */
    virtual bool loadSection(mtps::str const&)                           = 0;
};
}  // namespace haf::res

#endif
