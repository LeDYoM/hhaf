#include "loadedinstance.hpp"
#include "loadedinstance_private.hpp"

#include <string>

#include "loadedinstance_linux.cpp"
#include "loadedinstance_win.cpp"

namespace agloader
{
LoadedInstance::LoadedInstance() : priv_{new LoadedInstancePrivate}
{}

LoadedInstance::~LoadedInstance()
{
    unload();
    delete priv_;
}

namespace
{
std::string formatFileName(std::string fileName,
                           char const* const param_extension,
                           char const* const param_prefix)
{
    if (!fileName.ends_with(param_extension))
    {
        fileName += param_extension;
    }

    return param_prefix + fileName;
}

}  // namespace

bool LoadedInstance::load(char const* fileName)
{
    priv_->shared_file_handle =
        loadSharedObject(formatFileName(fileName, extension, prefix).c_str());
    return loaded();
}

void const* LoadedInstance::loadMethod(char const* methodName)
{
    if (loaded())
    {
        auto node = priv_->methods_.find(methodName);
        if (node == priv_->methods_.end())
        {
            auto methodAddress(
                getMethod(priv_->shared_file_handle, methodName));

            // Add the result of getMethod even if is nullptr to avoid
            // trying to load it more times
            priv_->methods_[methodName] = methodAddress;
            return methodAddress;
        }
        else
        {
            // The method is already on the map, return it
            return node->second;
        }
    }
    return nullptr;
}

bool LoadedInstance::loaded() const
{
    return priv_->shared_file_handle != nullptr;
}

bool LoadedInstance::unload()
{
    bool result{false};

    if (loaded())
    {
        result = freeSharedObject(priv_->shared_file_handle);
    }
    priv_->shared_file_handle = nullptr;
    priv_->methods_.clear();
    return result;
}

void const* LoadedInstance::loadedData() const
{
    return priv_->shared_file_handle;
}

}  // namespace agloader
