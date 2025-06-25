#include "haf_life_program_controller.hpp"

#include <haf/include/scene/iapp_initializer.hpp>
#include <haf/include/scene/iapp_finisher.hpp>
#include <hlog/include/hlog.hpp>

namespace hl
{

void HLProgramController::onInit(
    haf::scene::IAppInitializer& /*app_initializer*/)
{
    haf::DisplayLog::verbose("Initializing HLProgramController");
    //    app_initializer.registerSceneType<MenuScene>();
    //    app_initializer.registerSceneType<GameScene>();
    //    app_initializer.registerSceneType<HighScoresScene>();

    //    app_initializer.startScene<MenuScene>();
}

void HLProgramController::onFinish(haf::scene::IAppFinisher&)
{}

}  // namespace hl
