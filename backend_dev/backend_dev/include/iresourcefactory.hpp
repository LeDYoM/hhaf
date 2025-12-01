#ifndef HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <backend_dev/include/resource_load_parameters.hpp>

import htypes;

namespace haf::backend
{
template <typename T>
class IResourceFactory
{
public:
    virtual ~IResourceFactory() = default;

    virtual T* loadFromRawMemory(
        ResourceLoadParameters const& resource_load_parameters) = 0;
};
}  // namespace haf::backend

#endif
