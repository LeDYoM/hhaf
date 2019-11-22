#ifdef USE_DEBUG_ACTIONS

#include "debug_actions.hpp"
#include "gamescene.hpp"
#include "levelproperties.hpp"

#include <lib/include/liblog.hpp>

namespace zoper
{
using namespace lib::input;
using namespace lib::scene;

void DebugActions::onKeyPressed(const Key& key)
{
    gameScene()->levelProperties()->increaseScore(100);
}

void DebugActions::onKeyReleased(const Key& key)
{

}

GameScene* const DebugActions::gameScene()
{
    return attachedNodeAs<GameScene>();
}

} // namespace zoper

#endif
