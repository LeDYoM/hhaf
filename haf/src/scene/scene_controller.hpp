HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/component/component_factory.hpp>

namespace haf::sys
{
class SystemAccess;
class ISystemProvider;
}  // namespace haf::sys

namespace haf::scene
{
class SceneManager;

/**
 * @brief Class to control which @b Scene is active and which are not.
 * This controller class manages the creation, destruction and maintenance of
 * the @b Scene instances.
 */
class HAF_PRIVATE SceneController final
{
public:
    SceneController();

    void setSceneManager(htps::rptr<SceneManager> scene_manager);
    bool setSystemProviderInScene(
        htps::rptr<SceneComponent::SceneComponentPrivate> const scene_private,
        htps::rptr<sys::ISystemProvider> const isystem_provider);

    /**
     * @brief Switch to the next scene. For that to success, the current
     * scene shouold return the next scene in the member overriden
     * @b Scene::nextSceneName() and it has to be previously registered.
     */
    void switchToNextScene();
    void update();
    void finish();
    bool isActive();

    bool startScene(htps::str const& sceneName);

    template <typename T>
    bool registerAndStartScene(htps::str const& sceneName)
    {
        if (m_component_factory.registerObjectType<T>(sceneName))
        {
            return startScene(sceneName);
        }
        return false;
    }

    template <typename T>
    bool registerAndStartScene()
    {
        if (m_component_factory.registerObjectType<T>())
        {
            return startScene(T::StaticTypeName);
        }
        return false;
    }

    template <typename T>
    bool registerSceneNodeType()
    {
        return m_component_factory.registerObjectType<T>();
    }

    template <typename T>
    bool unregisterSceneNodeType()
    {
        return m_component_factory.unregisterObjectType<T>();
    }

    template <typename T>
    bool startScene()
    {
        return startScene(T::StaticTypeName);
    }

    component::ComponentFactory& componentFactory() noexcept;
    component::ComponentFactory const& componentFactory() const noexcept;

    SceneRenderContext& sceneRenderContext();
    SceneRenderContext const& sceneRenderContext() const;

    bool currentSceneIsNull();

    void requestExit();
    bool exitRequested() const;

    void addSceneRenderSubsystem(core::u32 const index);

private:
    void startScene(htps::sptr<SceneComponent> scene);
    void terminateCurrentScene();
    void deferredSwitchScene();

    component::ComponentFactory m_component_factory;
    htps::rptr<SceneManager> m_scene_manager{nullptr};
    htps::sptr<SceneComponent> m_current_scene{nullptr};
    htps::sptr<SceneNode> m_root_scene_node{nullptr};
    htps::uptr<SceneRenderContext> m_scene_render_context{nullptr};
    bool m_switch_scene{false};
    bool m_exit_requested{false};
};

}  // namespace haf::scene

#endif
