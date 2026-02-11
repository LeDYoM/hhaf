export module backend_dev:resource_load_parameters;

import :iresource_manager;
import htypes;

namespace haf::backend
{
export struct ResourceLoadParameters
{
    htps::str resource_id;
    htps::RawMemory raw_memory;
    htps::rptr<IResourceManager> iresource_manager;

    ResourceLoadParameters(htps::str r_id,
                           htps::RawMemory r_m,
                           htps::rptr<IResourceManager> ir_m) noexcept :
        resource_id{htps::move(r_id)},
        raw_memory{htps::move(r_m)},
        iresource_manager{htps::move(ir_m)}
    {}

    ResourceLoadParameters(ResourceLoadParameters const&) = default;
    ResourceLoadParameters& operator=(ResourceLoadParameters const&) = default;
    ResourceLoadParameters(ResourceLoadParameters&&) noexcept        = default;
    ResourceLoadParameters& operator=(ResourceLoadParameters&&) noexcept =
        default;
};

}  // namespace haf::backend
