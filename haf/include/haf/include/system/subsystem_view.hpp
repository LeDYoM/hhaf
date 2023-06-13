HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SUBSYSTEM_VIEW_INCLUDE_HPP
#define HAF_SYSTEM_SUBSYSTEM_VIEW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/subsystem_interface.hpp>
#include <haf/include/system/system_access.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::sys
{
class SystemAccess;

class SubSystemViewer
{
public:
    explicit SubSystemViewer(htps::rptr<ISystemProvider> isystem_provider) :
        isystem_provider_{isystem_provider}
    {}

    virtual ~SubSystemViewer() = default;

    template <typename SystemInterface_t>
    htps::rptr<SystemInterface_t> subSystem()
    {
        return subSystemInterface<SystemInterface_t>(isystem_provider_);
    }

    template <typename SystemInterface_t>
    htps::rptr<SystemInterface_t const> subSystem() const
    {
        return subSystemInterface<SystemInterface_t>(isystem_provider_);
    }

    htps::rptr<ISystemProvider> isystem_provider_;

private:
};
}  // namespace haf::sys

#endif
