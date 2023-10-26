HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_UPDATER_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_UPDATER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty_state.hpp>
#include <haf/include/debug_system/debug_types.hpp>

namespace haf::scene
{
    class ISceneManagerSubSystem;
}

namespace haf::component
{
class ComponentUpdater
{
public:
    void update(scene::ISceneManagerSubSystem& isceneManagerSubSystem);
protected:
    using UpdateFunction = core::function<bool()>;
    using UpdateProperty = core::rptr<prop::IPropertyState>;
    using UpdateAction   = core::function<void()>;

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

    void setParentSubSystem(core::str parent_sub_system_name) noexcept;

private:
    void update();

    core::vector<core::pair<UpdateFunction, UpdateAction>> m_propertiesToUpdate;
    core::str m_sceneParentSubSystemName;

//    HAF_DEBUG_VARIABLES_CODE(
//        static uint32_t m_updateCount[scene::size<scene::SceneUpdateTime>()]);
};

}  // namespace haf::component

#endif
