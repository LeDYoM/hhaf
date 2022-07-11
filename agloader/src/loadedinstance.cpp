#include "loadedinstance.hpp"
#include <map>
#include <string>

namespace
{
void updateFileExtension(std::string& fileName,
                                std::string const& extension)
{
    if (!fileName.ends_with(extension))
    {
        fileName += extension;
    }
}

std::string formatFileName(std::string fileName,
                                  char const* const extension,
                                  char const* const prefix)
{
    updateFileExtension(fileName, extension);
    return prefix + fileName;
}
}  // namespace

#if defined(_MSC_VER) || defined(__BORLANDC__)
#define WIN32_LEAN_AND_MEAN
#pragma warning( push )
#pragma warning( disable : 5039 )
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning( pop )

inline void* getMethod(void* handle, const char* methodName)
{
    return static_cast<void*>(
        GetProcAddress(static_cast<HMODULE>(handle), methodName));
}

inline void* loadSharedObject(const char* fileName)
{
    return static_cast<void*>(LoadLibrary(fileName));
}

inline bool freeSharedObject(void* handle)
{
    return (FreeLibrary(static_cast<HMODULE>(handle)) != 0);
}

constexpr char const extension[] = ".dll";
constexpr char const prefix[]    = "";

#else

// For now, windows or linux
#include <dlfcn.h>
inline void* getMethod(void* handle, char const* const methodName)
{
    return static_cast<void*>(dlsym(handle, methodName));
}

inline void* loadSharedObject(char const* const fileName)
{
    return static_cast<void*>(dlopen(fileName, RTLD_LAZY));
}

inline bool freeSharedObject(void* handle)
{
    return (dlclose(handle) == 0);
}

constexpr const char* const extension = ".so";
constexpr const char* const prefix    = "./lib";

#endif

namespace agloader
{
class LoadedInstancePrivate
{
public:
    void* shared_file_handle{nullptr};
    std::map<std::string, void*> methods_;
};

LoadedInstance::LoadedInstance() : priv_{new LoadedInstancePrivate}
{}

LoadedInstance::~LoadedInstance()
{
    unload();
    delete priv_;
}

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
