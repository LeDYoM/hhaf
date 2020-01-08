#include "zoperprogramcontroller.hpp"
#include "keymapping.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <mtypes/include/serializer.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/simulationsystem.hpp>
#include <lib/system/filesystem.hpp>
#include <lib/system/scenemanager.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

    ZoperProgramController::ZoperProgramController() {}
    ZoperProgramController::~ZoperProgramController() {}

    u16 ZoperProgramController::getVersion() const noexcept { return 1; }
    u16 ZoperProgramController::getSubVersion() const noexcept { return 4; }
    u16 ZoperProgramController::getPatch() const noexcept { return 0; }
    str ZoperProgramController::getName() const noexcept { return "Zoper"; }

    void ZoperProgramController::onInit()
    {
        gameSharedData = msptr<GameSharedData>();

        keyMapping = muptr<KeyMapping>();
        keyMapping->reset();
        systemProvider().fileSystem().deserializeFromFile("keys.txt", *keyMapping);
        systemProvider().fileSystem().serializeToFile("keys.txt", *keyMapping);

        {
            auto& sceneManager(systemProvider().sceneManager());
            sceneManager.setViewRect({0U,0U,2000U,2000U});
            auto& sceneController(sceneManager.sceneController());

            auto &scene_node_factory(sceneController->sceneNodeFactory());

            scene_node_factory.registerSceneNodeType<MenuScene>();
            scene_node_factory.registerSceneNodeType<GameScene>();
            scene_node_factory.registerSceneNodeType<HighScoresScene>();
            
            sceneController->setSceneDirector([this](const str& scene_name) -> str
            {
                // Did the user selected exit?
                if (gameSharedData->exitGame)
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

            // Hack to test high scores
            {
    //            gameData->score = 10000;
    //            sceneManager.startScene<HighScoresScene>();
            }

            sceneController->startScene<MenuScene>();
        }

//        systemProvider().timeSystem().setAcceleration(5.0F);
    }

    void ZoperProgramController::onFinish() { }
}
