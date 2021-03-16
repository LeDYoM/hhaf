#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/scene_components/include/app_initializer.hpp>
#include <haf/scene_components/include/app_finisher.hpp>
#include <haf/shareddata/include/shareddata.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

void ZoperProgramController::configureScenes(AppInitializer& app_initializer)
{
    app_initializer.registerSceneType<MenuScene>();
    app_initializer.registerSceneType<GameScene>();
    app_initializer.registerSceneType<HighScoresScene>();

    app_initializer.startScene<MenuScene>();
}

void ZoperProgramController::onInit(AppInitializer& app_initializer)
{
    DisplayLog::verbose("Initializing ZoperProgramController");
    configureScenes(app_initializer);
}

void ZoperProgramController::onFinish(AppFinisher&)
{}

}  // namespace zoper
