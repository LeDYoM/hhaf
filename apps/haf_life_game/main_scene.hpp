#ifndef HF_MAIN_SCENE_INCLUDE_HPP
#define HF_MAIN_SCENE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/scene_components/scene_component.hpp>

namespace haf::render
{
    class MeshComponent;
}

namespace haf::scene
{
    class SceneComponent;
}

namespace hl
{
class MainScene final
    : public haf::component::ComponentBase<"MainScene",
                                           haf::scene::SceneComponent>
{
public:
    MainScene();
    ~MainScene() override;

    void onAttached() override;

private:
    haf::ComponentSPtr<haf::render::MeshComponent>
        m_mesh_component;
};
}  // namespace hl

#endif
