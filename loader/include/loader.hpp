#ifndef AG_LOADER_INCLUDE_HPP
#define AG_LOADER_INCLUDE_HPP

#include "loader_export.hpp"

namespace loader
{
/**
 * @brief Main class to load a module
 * This class provides the basic API to load a module and its methods
 */
class Loader
{
public:
    /**
     * @brief Construct a new Loader objec.
     * Default constructor. Do not use it directly.
     */
    LOADER_PRIVATE Loader();

    /**
     * @brief Destroy the Loader object.
     * Destructor. Do not use it directly.
     */
    LOADER_PRIVATE ~Loader();

    LOADER_API void* loadModule(const char* const fileName);
    LOADER_API void* loadMethod(const char* const fileName, const char* const methodName);
    LOADER_API bool unloadModule(const char* const fileName);

private:
    class LoaderPrivate;
    LoaderPrivate* m_private;
};

LOADER_API Loader* createLoader();
LOADER_API void destroyLoader();
}  // namespace loader

#endif
