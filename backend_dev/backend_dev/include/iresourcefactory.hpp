#ifndef HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/rawmemory.hpp>

namespace haf::backend
{
template <typename T>
class IResourceFactory
{
public:
    virtual T* loadFromFile(const mtps::str&) = 0;
    virtual T* loadFromRawMemory(mtps::RawMemory*) { return nullptr; }
    virtual ~IResourceFactory() {}
};
}  // namespace haf::backend

#endif
