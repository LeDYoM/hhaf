#ifndef AG_LOADER_INCLUDE_HPP
#define AG_LOADER_INCLUDE_HPP

#include "loader_export.hpp"

namespace agloader
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

    /**
     * @brief Load a shared library module from a file
     * @param fileName File to load WITHOUT extension
     * @return Pointer to the loaded module.
     */
    LOADER_API void const* loadModule(const char* const fileName);

    /**
     * @brief Load a method from an already loaded module
     * @param fileName File name containing the already loaded module.
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    LOADER_API void const* loadMethod(const char* const fileName,
                                      const char* const methodName);

    /**
     * @brief Load a method from an already loaded module
     *
     * @tparam T Type to load
     * @param fileName File name containing the already loaded module.
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    template <typename T>
    T loadMethod(const char* const fileName, const char* const methodName)
    {
        return reinterpret_cast<T>(loadMethod(fileName, methodName));
    }

    /**
     * @brief Unload a module from a shared library.
     * @param fileName File containing the already loaded module
     * @return If the unloading was successful or not
     */
    LOADER_API bool unloadModule(const char* const fileName);

private:
    struct LoaderPrivate;
    LoaderPrivate* priv_{nullptr};
};

/**
 * @brief Create a Loader object
 * @return An instance of the loader class
 */
LOADER_API Loader* createLoader();

/**
 * @brief Destroy the loader
 */
LOADER_API void destroyLoader();

}  // namespace agloader

#endif
