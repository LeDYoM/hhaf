HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>
#include <haf/include/types/scene_types.hpp>
#include "scene_render_context_for_system.hpp"
#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>
#include "system/system_base.hpp"

#include <haf/include/component/component_factory.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/mesh_creator.hpp>
#include "scene_walker.hpp"
#include <haf/include/input/keyboard_input_manager.hpp>

namespace haf::scene
{
class SceneNode;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager final : public sys::SystemBase,
                                       public IAppInitializer,
                                       public IAppFinisher
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager() override;

    void init();
    void update();
    void finish();

    /**
     * @brief Tell the system to stop the current aplication.
     */
    void requestExit();

    template <typename T>
    bool registerComponent()
    {
        static_assert(std::is_base_of_v<component::Component, T>,
                      "The template type must be inherited from Component");
        auto const result{registerComponent(T::StaticTypeName,
                                            []() { return core::msptr<T>(); })};
        if (result)
        {
            DisplayLog::verbose("Registered component of type: <",
                                T::StaticTypeName, "> with size: ", sizeof(T));
        }
        return result;
    }

    bool registerComponent(
        core::str_view componentType,
        component::ComponentCreateFunction component_create_function) override;

    bool instanciateRootComponent(core::str_view componentType) override;
    core::sptr<component::Component> instantiateComponent(core::str_view name);

    core::rptr<SceneNode> rootSceneNode() const;

    SceneRenderContextForSystem& sceneRenderContextForSystem() noexcept;
    SceneRenderContextForSystem const& sceneRenderContextForSystem()
        const noexcept;

    SceneRenderContext& sceneRenderContext() noexcept;
    SceneRenderContext const& sceneRenderContext() const noexcept;

    SceneRenderContextView& sceneRenderContextView() noexcept;
    SceneRenderContextView const& sceneRenderContextView() const noexcept;

    MeshCreator& meshCreator() noexcept;
    MeshCreator const& meshCreator() const noexcept;

    evt::emitter<const input::Key&>& KeyPressed();
    evt::emitter<const input::Key&>& KeyReleased();

private:
    SceneRenderContextForSystem m_scene_render_context_for_system;
    input::KeyboardInputManager m_keyboard_input_manager;
    component::ComponentFactory m_component_factory;
    MeshCreator m_mesh_creator;
    core::uptr<SceneNode> m_rootSceneNode;
    SceneWalker m_scene_walker;

};
}  // namespace haf::scene

#endif
