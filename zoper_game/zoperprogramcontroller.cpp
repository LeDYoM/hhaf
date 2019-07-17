#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"

#include <lib/core/serializer.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/system/systemprovider.hpp>

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
        systemProvider().sceneManager().setViewRect({0,0,2000,2000});

        auto &scene_node_factory(systemProvider().sceneManager().sceneController()->sceneNodeFactory());

        scene_node_factory.registerSceneType<MenuScene>();
        scene_node_factory.registerSceneType<GameScene>();
        scene_node_factory.registerSceneType<HighScoresScene>();
        
        systemProvider().sceneManager().sceneController()->setSceneDirector([this](const str& scene_name) -> str
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
//            systemProvider().sceneManager().startFirstScene<HighScoresScene>();
        }

        systemProvider().sceneManager().sceneController()->startScene<MenuScene>();
    }

    void ZoperProgramController::onFinish() { }
}
