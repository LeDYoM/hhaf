#include "main_mesh_controller.hpp"
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/render/material_data_component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/scene_components/camera/debug_camera_component.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::render;

namespace hl
{

struct MainMeshController::ComponentsRequired
{};

struct MainMeshController::PrivateComponentData
{
    sptr<scene::TransformationComponent> m_transformation;
};

MainMeshController::MainMeshController() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

MainMeshController::~MainMeshController() = default;

void MainMeshController::onAttached()
{
    addUpdater({this, &MainMeshController::update});
    auto& c_container = attachedNode()->componentContainer();

    m_p->m_transformation =
        c_container.getOrCreateComponent<scene::TransformationComponent>();

    c_container.getOrCreateComponent<render::MaterialDataComponent>();
    c_container.getOrCreateComponent<render::MeshRenderComponent>();
}

bool MainMeshController::addRequirements(
    component::ComponentRequirements& /*component_requirements*/)
{
    bool isOk{true};
    //    isOk &= component_requirements.getOrCreateComponent(
    //        m_components->m_mesh_component);
    return isOk;
}

void MainMeshController::update()
{
    int a = 0;
    (void)(a);
    /*
        auto p{getComponent<MeshComponentTest>()
                   ->getComponent<TransformationComponent>()
                   ->Position()};
    //    p.x += 0.0001F;
        getComponent<MeshComponent>()
            ->getComponent<TransformationComponent>()
            ->Position = p;
    */
}

}  // namespace hl
