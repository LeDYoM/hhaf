#include "main_mesh_controller.hpp"
#include <haf/include/component/component_requirements.hpp>
#include <haf/include/scene_components/scene_nodes_component.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/render/mesh_render_component.hpp>

using namespace haf;
using namespace haf::scene;
using namespace haf::component;
using namespace haf::render;

namespace hl
{

MainMeshController::MainMeshController()
{}

MainMeshController::~MainMeshController() = default;

void MainMeshController::onAttached()
{
    addUpdater({this, &MainMeshController::update});
}

void MainMeshController::update()
{
    auto p{getComponent<MeshComponent>()
               ->getComponent<TransformationComponent>()
               ->Position()};
//    p.x += 0.0001F;
    getComponent<MeshComponent>()
        ->getComponent<TransformationComponent>()
        ->Position = p;
}

}  // namespace hl
