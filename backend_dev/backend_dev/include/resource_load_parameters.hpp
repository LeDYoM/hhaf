#ifndef HAF_BACKEND_RESOUCE_LOAD_PARAMETERS_INCLUDE_HPP
#define HAF_BACKEND_RESOUCE_LOAD_PARAMETERS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rawmemory.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/rawmemory.hpp>
#include <backend_dev/include/iresource_manager.hpp>

namespace haf::backend
{

struct ResourceLoadParameters
{
    htps::str resource_id;
    htps::RawMemory raw_memory;
    htps::rptr<IResourceManager> iresource_manager;

    ResourceLoadParameters(htps::str r_id,
                           htps::RawMemory r_m,
                           htps::rptr<IResourceManager> ir_m) :
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

#endif
