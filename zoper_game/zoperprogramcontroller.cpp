#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/scene_components/include/app_initializer.hpp>
#include <haf/shareddata/include/shareddata.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;
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

ZoperProgramController::ZoperProgramController()  = default;
ZoperProgramController::~ZoperProgramController() = default;

void ZoperProgramController::onInit(AppInitializer& app_initializer)
{
    DisplayLog::verbose("Initializing ZoperProgramController");
    configureScenes(app_initializer);
}

void ZoperProgramController::onFinish(haf::sys::DataWrapperCreator&)
{}

}  // namespace zoper
