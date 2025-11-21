module;

#include <string>

module agloader.linstance;
import agloader.linstance.pfunctions;

namespace agl
{
LoadedInstance::LoadedInstance()
{}

LoadedInstance::~LoadedInstance()
{
    unload();
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
    m_shared_file_handle =
        loadSharedObject(formatFileName(fileName, extension, prefix).c_str());
    return loaded();
}

void const* LoadedInstance::loadMethod(char const* methodName)
{
    if (loaded())
    {
        auto node{m_methods.find(methodName)};
        if (node == m_methods.end())
        {
            auto methodAddress{getMethod(m_shared_file_handle, methodName)};

            // Add the result of getMethod even if is nullptr to avoid
            // trying to load it more times
            m_methods[methodName] = methodAddress;
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
    return m_shared_file_handle != nullptr;
}

bool LoadedInstance::unload()
{
    bool result{false};

    if (loaded())
    {
        result = freeSharedObject(m_shared_file_handle);
    }
    m_shared_file_handle = nullptr;
    m_methods.clear();
    return result;
}

void const* LoadedInstance::loadedData() const
{
    return m_shared_file_handle;
}

}  // namespace agl
