module;

#include <map>
#include <string>
#include <memory>

export module agloader;

import "loader_export.hpp";
import :linstance;

namespace agl
{
/**
 * @brief Main class to load a module
 * This class provides the basic API to load a module and its methods
 */
export class Loader
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
    T loadMethod(const char* const fileName,
                 const char* const methodName)
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
    std::map<std::string, std::shared_ptr<LoadedInstance>> m_loaded_instances;
};

static std::unique_ptr<Loader> loaderInstance;
static uintmax_t reference_counter{0U};

/**
 * @brief Create a Loader object
 * @return An instance of the loader class
 */
export LOADER_API Loader* createLoader()
{
    ++reference_counter;
    if (loaderInstance == nullptr)
    {
        loaderInstance = std::make_unique<Loader>();
    }

    return loaderInstance.get();
}

/**
 * @brief Destroy the loader
 */
export LOADER_API void destroyLoader()
{
    if (reference_counter > 0U)
    {
        --reference_counter;
    }

    if (reference_counter == 0U)
    {
        loaderInstance.reset(nullptr);
    }
}

}  // namespace agl

module :private;

namespace agl
{
Loader::Loader() = default;

Loader::~Loader() = default;

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    loadedInstace->load(fileName);

    if (loadedInstace->loaded())
    {
        m_loaded_instances[fileName] = loadedInstace;
    }
    return loadedInstace->loadedData();
}

void const* Loader::loadMethod(const char* const fileName,
                               const char* const methodName)
{
    if (auto const iterator{m_loaded_instances.find(fileName)};
        iterator != m_loaded_instances.end())
    {
        auto loadedInstance{(*iterator).second};
        return loadedInstance->loadMethod(methodName);
    }
    return nullptr;
}

bool Loader::unloadModule(const char* const fileName)
{
    if (auto const iterator{m_loaded_instances.find(fileName)};
        iterator != m_loaded_instances.end())
    {
        m_loaded_instances.erase(iterator);
        return true;
    }

    return false;
}

}  // namespace agl
