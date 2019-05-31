#include "gamescenedata.hpp"
#include "gamescene.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/core/host.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    void GameSceneData::createData(GameScene &gameScene, const GameMode gameMode)
    {
        gameScene.loadResources(GameResources{});
        auto resources_viewer = gameScene.dataWrapper<ResourceView>();
    }
}
