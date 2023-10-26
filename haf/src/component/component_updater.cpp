#include <haf/include/component/component_updater.hpp>
#include "scene/iscene_manager subsystem.hpp"

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
    if (m_sceneParentSubSystemName == isceneManagerSubSystem.subSystemName())
    {
        update();
    }
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
