#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <haf/include/scene/iapp_initializer.hpp>
#include <haf/include/scene/iapp_finisher.hpp>
#include <hlog/include/hlog.hpp>

namespace zoper
{

void ZoperProgramController::onInit(
    haf::scene::IAppInitializer& app_initializer)
{
    DisplayLog::verbose("Initializing ZoperProgramController");
    app_initializer.registerSceneComponent<Menu>();
    app_initializer.registerSceneComponent<Game>();
    app_initializer.registerSceneComponent<HighScores>();

    app_initializer.startScene<Menu>();
}

void ZoperProgramController::onFinish(haf::scene::IAppFinisher&)
{}

}  // namespace zoper
