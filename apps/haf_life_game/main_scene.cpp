#include "main_scene.hpp"
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/2.1/scene_nodes_component.hpp>
#include <haf/include/scene_components/2.1/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/render/mesh_component.hpp>

#include "main_mesh_controller.hpp"

using namespace haf;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::render;

namespace hl
{

MainScene::MainScene()
{}

MainScene::~MainScene() = default;

void MainScene::onAttached()
{
    getComponent<SceneComponent>()
        ->getComponent<SceneNodesComponent>()
        ->createSceneNodeWithComponent<MainMeshController>(
            "MainMeshController");
}

}  // namespace hl
