#include "zoperprogramcontroller.hpp"
#include "keymapping.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"
#include "gameshareddata.hpp"

#include <mtypes/include/serializer.hpp>
#include <haf/filesystem/include/fileserializer.hpp>
#include <haf/scene_components/include/scenemetrics.hpp>
#include <haf/scene_components/include/scenefactory.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>
#include <haf/shareddata/include/shareddata.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

void ZoperProgramController::configureScenes(
    haf::sys::DataWrapperCreator& data_wrapper_creator)
{
        auto scene_node_factory(
            data_wrapper_creator.dataWrapper<scene::SceneFactory>());

        scene_node_factory->registerSceneType<MenuScene>();
        scene_node_factory->registerSceneType<GameScene>();
        scene_node_factory->registerSceneType<HighScoresScene>();

        auto scene_control(
            data_wrapper_creator.dataWrapper<scene::SceneControl>());

        scene_control->startScene<MenuScene>();
}

ZoperProgramController::ZoperProgramController()  = default;
ZoperProgramController::~ZoperProgramController() = default;

void ZoperProgramController::onInit(
    haf::sys::DataWrapperCreator& data_wrapper_creator)
{
    DisplayLog::verbose("Initializing ZoperProgramController");

    keyMapping = muptr<KeyMapping>();
    keyMapping->reset();

    data_wrapper_creator.dataWrapper<sys::FileSerializer>()
        ->deserializeFromFile("keys.txt", *keyMapping);
    data_wrapper_creator.dataWrapper<sys::FileSerializer>()->serializeToFile(
        "keys.txt", *keyMapping);

    {
        GameSharedData game_shared_data{};
        data_wrapper_creator.dataWrapper<shdata::SharedData>()->store(
            GameSharedData::address(), game_shared_data);
    }
    {
        data_wrapper_creator.dataWrapper<scene::SceneMetrics>()->setViewRect(
            {0U, 0U, 2000U, 2000U});
    }

    configureScenes(data_wrapper_creator);
}

void ZoperProgramController::onFinish(
    haf::sys::DataWrapperCreator&)
{
//    const bool check =
//        data_wrapper_creator.dataWrapper<shdata::SharedData>()->makeEmpty();
//    LogAsserter::log_assert(check, "SharedData is empty!");
}

}  // namespace zoper
