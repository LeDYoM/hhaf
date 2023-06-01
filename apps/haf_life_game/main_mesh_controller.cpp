#include "main_mesh_controller.hpp"
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/render/material_data_component.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::render;

namespace hl
{

struct MainMeshController::ComponentsRequired
{
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
    auto transform{
        attachedNode()
            ->createSceneNodeWithComponent<scene::TransformationComponent>(
                "Transformation_0")};
    auto material_{
        transform->attachedNode()
            ->createSceneNodeWithComponent<render::MaterialDataComponent>(
                "Material_0")};
    auto mesh{material_->attachedNode()
            ->createSceneNodeWithComponent<render::MeshRenderComponent>(
                "Mesh_0")};
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
    int a=0;
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
