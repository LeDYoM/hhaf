module;

#include <map>
#include <string>

export module agloader:linstance;

import :pfunctions;
import :utils;

namespace agl
{
class LoadedInstance
{
public:
    LoadedInstance() = default;
    ~LoadedInstance() = default;

    bool load(const char* fileName)
    {
        m_shared_file_handle = loadSharedObject(
            formatFileName(fileName, extension, prefix).c_str());
        return loaded();
    }

    void const* loadMethod(const char* methodName)
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

    bool loaded() const
    {
        return m_shared_file_handle != nullptr;
    }

    bool unload()
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

    void const* loadedData() const { return m_shared_file_handle; }

private:
    void* m_shared_file_handle{nullptr};
    std::map<std::string, void*> m_methods;
};
}  // namespace agl
