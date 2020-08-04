#include "zoperprogramcontroller.hpp"
#include "keymapping.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"
#include "gameshareddata.hpp"
#include "app_version.hpp"

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
ZoperProgramController::ZoperProgramController() = default;
ZoperProgramController::~ZoperProgramController() = default;
/*
u16 ZoperProgramController::getVersion() const noexcept
{
    return cl_version::VersionMajor;
}

u16 ZoperProgramController::getSubVersion() const noexcept
{
    return cl_version::VersionMinor;
}

u16 ZoperProgramController::getPatch() const noexcept
{
    return cl_version::VersionPatch;
}

str ZoperProgramController::getName() const noexcept
{
    return cl_version::ProjectName;
}
*/
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
        auto game_shared_data{muptr<GameSharedData>()};
        data_wrapper_creator.dataWrapper<shdata::SharedData>()->store(
            std::move(game_shared_data));
    }
    {
        data_wrapper_creator.dataWrapper<scene::SceneMetrics>()->setViewRect(
            {0U, 0U, 2000U, 2000U});
        auto scene_node_factory(
            data_wrapper_creator.dataWrapper<scene::SceneFactory>());

        scene_node_factory->registerSceneType<MenuScene>();
        scene_node_factory->registerSceneType<GameScene>();
        scene_node_factory->registerSceneType<HighScoresScene>();

        auto scene_control(
            data_wrapper_creator.dataWrapper<scene::SceneControl>());

        scene_control->setSceneDirector([this](const str& scene_name) -> str {
            if (scene_name == (MenuScene::StaticTypeName))
            {
                return GameScene::StaticTypeName;
            }
            else if (scene_name == (GameScene::StaticTypeName))
            {
                return HighScoresScene::StaticTypeName;
            }
            else if (scene_name == (HighScoresScene::StaticTypeName))
            {
                return MenuScene::StaticTypeName;
            }
            return str{};
        });

        scene_control->startScene<MenuScene>();
    }
}

void ZoperProgramController::onFinish(
    haf::sys::DataWrapperCreator& data_wrapper_creator)
{
    const bool check =
        data_wrapper_creator.dataWrapper<shdata::SharedData>()->makeEmpty();
    LogAsserter::log_assert(check, "SharedData is empty!");
}

}  // namespace zoper
