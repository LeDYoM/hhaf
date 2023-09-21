HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_UPDATER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_UPDATER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty_state.hpp>

namespace haf::scene
{
enum class SceneUpdateTime : core::u32;
}

namespace haf::component
{
class ComponentUpdater
{
protected:
    using UpdateFunction = core::function<bool()>;
    using UpdateProperty = core::rptr<prop::IPropertyState>;
    using UpdateAction   = core::function<void()>;

    void update(scene::SceneUpdateTime const sceneUpdateTime);

    /**
     * @brief Add an updater of a property
     *
     * @param updateAction Action to be called
     * @param updateProperty PropertyState pointer to check
     */
    void addUpdater(UpdateAction updateAction, UpdateProperty updateProperty);
    void addUpdater(UpdateAction updateAction, UpdateFunction updateProperty);

    template <typename... Args>
    void addUpdater(UpdateAction updateAction, Args*... updateProperties)
    {
        addUpdater(core::move(updateAction), [updateProperties...]() {
            return prop::ps_readResetHasAnyChanged((*(updateProperties))...);
        });
    }

    void addUpdater(UpdateAction updateAction);

    void setSceneUpdateTime(
        scene::SceneUpdateTime const sceneUpdateTime) noexcept;

private:
    void update();

    core::vector<core::pair<UpdateFunction, UpdateAction>> m_propertiesToUpdate;
    scene::SceneUpdateTime m_sceneUpdateTime;
};

}  // namespace haf::component

#endif
