#ifndef HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/rawmemory.hpp>
#include <backend_dev/include/resource_load_parameters.hpp>

namespace haf::backend
{
template <typename T>
class IResourceFactory
{
public:
    virtual T* loadFromRawMemory(htps::RawMemory*, IResourceManager*)
    {
        return nullptr;
    }
    virtual T* loadFromRawMemory(htps::RawMemory*) { return nullptr; }
    virtual ~IResourceFactory() {}
};
}  // namespace haf::backend

#endif
