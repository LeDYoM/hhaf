#include "zoperprogramcontroller.hpp"
#include "keymapping.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"
#include "gameshareddata.hpp"

#include <mtypes/include/serializer.hpp>
#include <haf/system/i_include/systemprovider.hpp>
#include <haf/system/i_include/get_systemprovider.hpp>
#include <haf/filesystem/include/fileserializer.hpp>
#include <haf/scene/i_include/scenecontroller.hpp>
#include <haf/scene/i_include/scenemanager.hpp>
#include <haf/scene_components/include/scenemetrics.hpp>
#include <haf/shareddata/include/shareddataview.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

ZoperProgramController::ZoperProgramController()
{}
ZoperProgramController::~ZoperProgramController()
{}

u16 ZoperProgramController::getVersion() const noexcept
{
    return 1;
}
u16 ZoperProgramController::getSubVersion() const noexcept
{
    return 4;
}
u16 ZoperProgramController::getPatch() const noexcept
{
    return 0;
}
str ZoperProgramController::getName() const noexcept
{
    return "Zoper";
}

void ZoperProgramController::onInit(
    sys::ISystemProvider& system_provider,
    haf::sys::DataWrapperCreator& data_wrapper_creator)
{
    DisplayLog::verbose("Initializing ZoperProgramController");
    sys::SystemProvider& systemprovider =
        sys::getSystemProvider(system_provider);

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
        auto& sceneManager(systemprovider.sceneManager());
        auto& sceneController(sceneManager.sceneController());
        auto& scene_node_factory(sceneController->sceneNodeFactory());

        scene_node_factory.registerSceneNodeType<MenuScene>();
        scene_node_factory.registerSceneNodeType<GameScene>();
        scene_node_factory.registerSceneNodeType<HighScoresScene>();

        sceneController->setSceneDirector(
            [this, &system_provider](const str& scene_name) -> str {
                // Did the user selected exit?
                if (sys::getSystemProvider(system_provider).exitRequested())
                {
                    return str{};
                }
                else if (scene_name == (MenuScene::StaticTypeName))
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

        sceneController->startScene<MenuScene>();
    }
}

void ZoperProgramController::onFinish(
    sys::ISystemProvider& system_provider,
    haf::sys::DataWrapperCreator& data_wrapper_creator)
{
    const bool check =
        data_wrapper_creator.dataWrapper<shdata::SharedData>()->makeEmpty();
    LogAsserter::log_assert(check, "SharedData is empty!");
}

}  // namespace zoper
