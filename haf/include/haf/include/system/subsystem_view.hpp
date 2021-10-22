#ifndef HAF_SYSTEM_SUBSYSTEM_VIEW_INCLUDE_HPP
#define HAF_SYSTEM_SUBSYSTEM_VIEW_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/system/systemaccess.hpp>
#include <haf/include/system/subsystem_interface.hpp>

namespace haf::sys
{
class SubSystemViewer
{
public:
    explicit SubSystemViewer(types::rptr<SystemAccess> system_access)
        : system_access_{system_access} {}
    virtual ~SubSystemViewer() = default;

    template <typename SystemInterface_t>
    types::rptr<SystemInterface_t> subSystem()
    {
        return subSystemInterface<SystemInterface_t>(system_access_);
    }

    template <typename SystemInterface_t>
    types::rptr<SystemInterface_t const> subSystem() const
    {
        return subSystemInterface<SystemInterface_t>(system_access_);
    }

private:
    types::rptr<SystemAccess> system_access_;
};
}  // namespace haf::sys

#endif
