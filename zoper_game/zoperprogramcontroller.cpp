#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/include/scene_components/app_initializer.hpp>
#include <haf/include/scene_components/app_finisher.hpp>
#include <haf/include/shareddata/shareddata.hpp>
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

u16 ZoperProgramController::getVersion() const noexcept
{
    return Zoper_VERSION;
}

u16 ZoperProgramController::getSubVersion() const noexcept
{
    return Zoper_VERSION;
}

u16 ZoperProgramController::getPatch() const noexcept
{
    return Zoper_VERSION;
}

u16 ZoperProgramController::getTweak() const noexcept
{
    return Zoper_VERSION;
}

str ZoperProgramController::getName() const noexcept
{
    return "";
}

}  // namespace zoper
