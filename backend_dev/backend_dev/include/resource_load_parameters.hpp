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
    htps::rptr<htps::RawMemory> raw_memory;
    htps::rptr<IResourceManager> iresource_manager;
};

}  // namespace haf::backend

#endif
