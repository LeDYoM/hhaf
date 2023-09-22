#include <haf/include/component/component_updater.hpp>

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

void ComponentUpdater::update(scene::SceneUpdateTime const sceneUpdateTime)
{
    if (m_sceneUpdateTime == sceneUpdateTime)
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

void ComponentUpdater::setSceneUpdateTime(
    scene::SceneUpdateTime const sceneUpdateTime) noexcept
{
    m_sceneUpdateTime = sceneUpdateTime;
}

}  // namespace haf::component
