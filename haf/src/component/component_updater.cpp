#include <haf/include/component/component_updater.hpp>
#include "scene_subsystems/iscene_manager subsystem.hpp"

namespace haf::component
{
void ComponentUpdater::addUpdater(UpdateAction updateAction,
                                  UpdateProperty updateProperty)
{
    m_propertiesToUpdate.emplace_back(
        [updateProperty = core::move(updateProperty)]() {
            return prop::ps_readResetHasChanged(*updateProperty);
        },
        core::move(updateAction));
}

void ComponentUpdater::addUpdater(UpdateAction updateAction,
                                  UpdateFunction updateFunction)
{
    m_propertiesToUpdate.emplace_back(core::move(updateFunction),
                                      core::move(updateAction));
}

void ComponentUpdater::addUpdater(UpdateAction updateAction)
{
    m_propertiesToUpdate.emplace_back(nullptr, core::move(updateAction));
}

void ComponentUpdater::update(
    scene::ISceneManagerSubSystem& isceneManagerSubSystem)
{
    if (acceptSubSystem(isceneManagerSubSystem) &&
        isceneManagerSubSystem.isComponentAcceptable(*this))
    {
        isceneManagerSubSystem.performUpdateAction(*this);
        update();
    }
}

bool ComponentUpdater::acceptSubSystem(
    scene::ISceneManagerSubSystem& isceneManagerSubSystem)
{
    //    (void)(isceneManagerSubSystem);
    //    return true;
    return m_sceneParentSubSystemName == isceneManagerSubSystem.subSystemName();
}

void ComponentUpdater::update()
{
    for (auto&& updater : m_propertiesToUpdate)
    {
        if (!updater.first || (updater.first)())
        {
            (updater.second)();
        }
    }
}

void ComponentUpdater::setParentSubSystem(
    core::str parent_sub_system_name) noexcept
{
    m_sceneParentSubSystemName = core::move(parent_sub_system_name);
}

}  // namespace haf::component
