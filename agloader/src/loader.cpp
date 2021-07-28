#include <agloader/include/loader.hpp>
#include "loadedinstance.hpp"
#include <string>
#include <map>
#include <memory>
#include <cstdint>

namespace agloader
{
struct Loader::LoaderPrivate
{
    std::map<std::string, std::shared_ptr<LoadedInstance>> m_loadedInstances;
};

static std::unique_ptr<Loader> loaderInstance;
static uintmax_t reference_counter{0U};

Loader::Loader()
{
    m_private = new LoaderPrivate;
}

Loader::~Loader()
{
    if (m_private)
    {
        m_private->m_loadedInstances.clear();
        delete m_private;
        m_private = nullptr;
    }
}

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    loadedInstace->load(fileName);

    if (loadedInstace->loaded())
    {
        m_private->m_loadedInstances[fileName] = loadedInstace;
    }
    return loadedInstace->loadedData();
}

void const* Loader::loadMethod(const char* const fileName,
                         const char* const methodName)
{
    auto iterator{m_private->m_loadedInstances.find(fileName)};
    if (iterator != m_private->m_loadedInstances.end())
    {
        auto loadedInstance{(*iterator).second};
        return loadedInstance->loadMethod(methodName);
    }
    return nullptr;
}

bool Loader::unloadModule(const char* fileName)
{
    auto iterator{m_private->m_loadedInstances.find(fileName)};
    if (iterator != m_private->m_loadedInstances.end())
    {
        m_private->m_loadedInstances.erase(iterator);
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
