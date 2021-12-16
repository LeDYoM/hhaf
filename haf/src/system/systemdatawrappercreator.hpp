#ifndef HAF_SYSTEM_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/system/isystem_provider.hpp>
#include "system_base.hpp"
#include "system/system_provider.hpp"

namespace haf::sys
{
class SystemDataWrapperCreator : public SystemAccess, public DataWrapperCreator
{
public:
    explicit SystemDataWrapperCreator(SystemBase& system_base) noexcept :
        SystemAccess{&(system_base.isystemProvider())}, DataWrapperCreator{this}
    {}

    explicit SystemDataWrapperCreator(SystemProvider& system_provider) noexcept
        :
        SystemAccess{&system_provider}, DataWrapperCreator{this}
    {}
};
}  // namespace haf::sys

#endif
