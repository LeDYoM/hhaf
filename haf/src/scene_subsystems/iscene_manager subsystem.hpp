HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_ISCENEMANAGER_SUBSYSTEM_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>

namespace haf::component
{
class ComponentUpdater;
}

namespace haf::scene
{
class ISceneManagerSubSystem
{
public:
    explicit ISceneManagerSubSystem(core::str subsystem_name);
    virtual ~ISceneManagerSubSystem();

    core::str const& subSystemName() const noexcept { return m_subsystem_name; }
    virtual bool isComponentAcceptable(
        component::ComponentUpdater& component_updater);

    virtual void performUpdateAction(
        component::ComponentUpdater& component_updater);

private:
    core::str m_subsystem_name;
};
}  // namespace haf::scene

#endif
