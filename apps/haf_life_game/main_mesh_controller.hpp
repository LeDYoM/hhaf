#ifndef HF_MAIN_MESH_CONTROLLER_INCLUDE_HPP
#define HF_MAIN_MESH_CONTROLLER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/scene_components/2.1/scene_component.hpp>
#include <haf/include/render/mesh_component.hpp>

namespace hl
{
class MainMeshController final
    : public haf::component::ComponentBase<"MainMeshController",
                                           haf::render::MeshComponent>
{
public:
    MainMeshController();
    ~MainMeshController() override;

    void onAttached() override;
    void update();
};
}  // namespace hl

#endif
