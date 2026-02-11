export module backend_dev:iresource_factory;

import htypes;
import :resource_load_parameters;

namespace haf::backend
{
export template <typename T>
class IResourceFactory
{
public:
    virtual ~IResourceFactory() = default;

    virtual T* loadFromRawMemory(
        ResourceLoadParameters const& resource_load_parameters) = 0;
};
}  // namespace haf::backend
