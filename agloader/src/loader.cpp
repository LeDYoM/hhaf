module;

#include "loadedinstance.hpp"
#include "loader_private.cpp"

#include <string>
#include <map>
#include <memory>
#include <cstdint>

module agloader;

namespace agloader
{
static std::unique_ptr<Loader> loaderInstance;
static uintmax_t reference_counter{0U};

Loader::Loader()
{
    m_priv = new LoaderPrivate;
}

Loader::~Loader()
{
    if (m_priv)
    {
        m_priv->m_loaded_instances.clear();
        delete m_priv;
        m_priv = nullptr;
    }
}

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    loadedInstace->load(fileName);

    if (loadedInstace->loaded())
    {
        m_priv->m_loaded_instances[fileName] = loadedInstace;
    }
    return loadedInstace->loadedData();
}

void const* Loader::loadMethod(const char* const fileName,
                               const char* const methodName)
{
    auto iterator{m_priv->m_loaded_instances.find(fileName)};
    if (iterator != m_priv->m_loaded_instances.end())
    {
        auto loadedInstance{(*iterator).second};
        return loadedInstance->loadMethod(methodName);
    }
    return nullptr;
}

bool Loader::unloadModule(const char* fileName)
{
    auto iterator{m_priv->m_loaded_instances.find(fileName)};
    if (iterator != m_priv->m_loaded_instances.end())
    {
        m_priv->m_loaded_instances.erase(iterator);
        return true;
    }
    return false;
}

Loader* createLoader()
{
    ++reference_counter;
    if (loaderInstance == nullptr)
    {
        loaderInstance = std::make_unique<Loader>();
    }

    return loaderInstance.get();
}

void destroyLoader()
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
}  // namespace agloader
