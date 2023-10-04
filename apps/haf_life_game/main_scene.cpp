#include "main_scene.hpp"
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/camera/camera.hpp>
#include <haf/include/scene_components/transformation_component.hpp>

#include "main_mesh_controller.hpp"

using namespace haf;
using namespace haf::core;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::render;

namespace hl
{

struct MainScene::ComponentsRequired
{
    sptr<haf::scene::SceneComponent> m_scene_component;
};

struct MainScene::PrivateComponentData
{};

MainScene::MainScene() :
    m_components{make_pimplp<ComponentsRequired>()},
    m_p{make_pimplp<PrivateComponentData>()}
{}

MainScene::~MainScene() = default;

bool MainScene::addRequirements(
    component::ComponentRequirements& component_requirements)
{
    bool isOk{true};
    isOk &= component_requirements.getOrCreateComponent(
        m_components->m_scene_component);
    return isOk;
}

void MainScene::onAttached()
{
    auto node{attachedNode()->sceneNodesGroup().createSceneNode("node")};
    CameraBuilder cbuilder;
    cbuilder.addDebugMovableCamera(*node);
//    node->componentContainer().attachComponent()
    /*
        attachedNode()
            ->sceneNodesGroup()
            .createSceneNodeWithComponent<DebugCameraComponent>(
                "DebugCameraComponent");
    */
    auto scene_node_component =
        attachedNode()
            ->sceneNodesGroup()
            .createSceneNodeWithComponent<MainMeshController>(
                "MainMeshController");
/*
    scene_node_component->attachedNode()
        ->componentContainer()
        .getExistingComponent<TransformationComponent>()
        ->Position = {0.5F, 0.5F, 0.0F};
*/
}

}  // namespace hl
