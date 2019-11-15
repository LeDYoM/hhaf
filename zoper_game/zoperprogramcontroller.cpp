#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <lib/core/serializer.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/simulationsystem.hpp>

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
        Serializer<KeyMapping> kmSerializer;
        kmSerializer.deserialize("keyboard.txt", *keyMapping);

        {
            auto& sceneManager(systemProvider().sceneManager());
            sceneManager.setViewRect({0,0,2000,2000});
            auto& sceneController(sceneManager.sceneController());

            auto &scene_node_factory(sceneController->sceneNodeFactory());

            scene_node_factory.registerSceneNodeType<MenuScene>();
            scene_node_factory.registerSceneNodeType<GameScene>();
            scene_node_factory.registerSceneNodeType<HighScoresScene>();
            
            sceneController->setSceneDirector([this](const str& scene_name) -> str
            {
                if (scene_name == (MenuScene::StaticTypeName))
                {
                    // Did the user selected exit?
                    if (gameSharedData->exitGame) {
                        return str();
                    }
                    return GameScene::StaticTypeName;
                }
                return MenuScene::StaticTypeName;
            });

            // Hack to test high scores
            {
    //            gameData->score = 10000;
    //            sceneManager.startFirstScene<HighScoresScene>();
            }

            sceneController->startScene<MenuScene>();
        }

//        systemProvider().timeSystem().setAcceleration(5.0F);
    }

    void ZoperProgramController::onFinish() { }
}
