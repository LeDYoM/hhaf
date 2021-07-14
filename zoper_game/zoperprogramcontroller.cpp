#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/include/scene_components/app_initializer.hpp>
#include <haf/include/scene_components/app_finisher.hpp>
#include <hlog/include/hlog.hpp>

namespace zoper
{

void ZoperProgramController::onInit(haf::scene::AppInitializer& app_initializer)
{
    DisplayLog::verbose("Initializing ZoperProgramController");
    app_initializer.registerSceneType<MenuScene>();
    app_initializer.registerSceneType<GameScene>();
    app_initializer.registerSceneType<HighScoresScene>();

    app_initializer.startScene<MenuScene>();
}

void ZoperProgramController::onFinish(haf::scene::AppFinisher&)
{}

}  // namespace zoper
