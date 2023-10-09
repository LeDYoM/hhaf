#include <haf/include/scene_components/main_mesh_controller.hpp>
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/render/material_data_component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/scene_components/camera/debug_camera_component.hpp>
#include <haf/include/math/types.hpp>

using namespace haf::core;
using namespace haf::component;
using namespace haf::render;

namespace haf::scene
{

struct MainMeshController::ComponentsRequired
{
    sptr<TransformationComponent> m_transformation;
    sptr<render::MaterialDataComponent> m_material_data_component;
    sptr<render::MeshRenderComponent> m_mesh_render_component;
};

struct MainMeshController::PrivateComponentData
{};

MainMeshController::MainMeshController() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

MainMeshController::~MainMeshController() = default;

void MainMeshController::onAttached()
{
    addUpdater({this, &MainMeshController::update});
}

bool MainMeshController::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};

    component_requirements.getOrCreateComponent(m_components->m_transformation);

    component_requirements.getOrCreateComponent(
        m_components->m_material_data_component);
    component_requirements.getOrCreateComponent(
        m_components->m_mesh_render_component);

    m_components->m_transformation->Position =
        math::vector3df{0.5F, 0.0F, 0.0F};

    return isOk;
}

void MainMeshController::update()
{
}

}  // namespace hl
