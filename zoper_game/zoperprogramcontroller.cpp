#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>
#include <hlog/include/hlog.hpp>

namespace zoper
{

void ZoperProgramController::onInit(
    haf::scene::IAppInitializer& app_initializer)
{
    logger::DisplayLog::verbose("Initializing ZoperProgramController");
    app_initializer.registerSceneType<MenuScene>();
    app_initializer.registerSceneType<GameScene>();
    app_initializer.registerSceneType<HighScoresScene>();

    app_initializer.startScene<MenuScene>();
}

void ZoperProgramController::onFinish(haf::scene::IAppFinisher&)
{}

}  // namespace zoper
