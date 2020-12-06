#ifndef HAF_SYSTEM_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/datawrappercreator.hpp>
#include <haf/system/include/systemaccess.hpp>
#include "systembase.hpp"

namespace haf::sys
{
class SystemDataWrapperCreator : public SystemAccess, public DataWrapperCreator
{
public:
    explicit SystemDataWrapperCreator(SystemBase& system_base) noexcept :
        SystemAccess{&(system_base.isystemProvider())}, DataWrapperCreator{this}
    {}
};
}  // namespace haf::sys

#endif
