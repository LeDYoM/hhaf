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
    bool update(component::ComponentUpdater& component_updater);

    core::str const& subSystemName() const noexcept { return m_subsystem_name; }

private:
    virtual bool isComponentAcceptable(component::ComponentUpdater& component_updater);
    core::str m_subsystem_name;
};
}  // namespace haf::scene

#endif
