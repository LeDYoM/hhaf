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
    std::map<std::string, std::shared_ptr<LoadedInstance>> loaded_instances_;
};

static std::unique_ptr<Loader> loaderInstance;
static uintmax_t reference_counter{0U};

Loader::Loader()
{
    priv_ = new LoaderPrivate;
}

Loader::~Loader()
{
    if (priv_)
    {
        priv_->loaded_instances_.clear();
        delete priv_;
        priv_ = nullptr;
    }
}

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    loadedInstace->load(fileName);

    if (loadedInstace->loaded())
    {
        priv_->loaded_instances_[fileName] = loadedInstace;
    }
    return loadedInstace->loadedData();
}

void const* Loader::loadMethod(const char* const fileName,
                         const char* const methodName)
{
    auto iterator{priv_->loaded_instances_.find(fileName)};
    if (iterator != priv_->loaded_instances_.end())
    {
        auto loadedInstance{(*iterator).second};
        return loadedInstance->loadMethod(methodName);
    }
    return nullptr;
}

bool Loader::unloadModule(const char* fileName)
{
    auto iterator{priv_->loaded_instances_.find(fileName)};
    if (iterator != priv_->loaded_instances_.end())
    {
        priv_->loaded_instances_.erase(iterator);
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
