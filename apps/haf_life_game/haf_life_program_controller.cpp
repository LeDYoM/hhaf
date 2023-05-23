#include "haf_life_program_controller.hpp"

#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>
#include <hlog/include/hlog.hpp>

#include "main_scene.hpp"
#include "main_mesh_controller.hpp"

namespace hl
{

void HLProgramController::onInit(
    haf::scene::IAppInitializer& app_initializer)
{
    haf::DisplayLog::verbose("Initializing HLProgramController");
    app_initializer.registerComponent<MainScene>();
    app_initializer.registerComponent<MainMeshController>();

    app_initializer.instanciateRootComponent("MainScene");
//    app_initializer.registerSceneType<MenuScene>();
//    app_initializer.registerSceneType<GameScene>();
//    app_initializer.registerSceneType<HighScoresScene>();

//    app_initializer.startScene<MenuScene>();
}

void HLProgramController::onFinish(haf::scene::IAppFinisher&)
{}

}  // namespace hl
