#ifdef USE_DEBUG_ACTIONS

#include "debug_actions.hpp"
#include "gamescene.hpp"
#include "levelproperties.hpp"

#include <haf/include/liblog.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf::scene;
using namespace haf::input;

void DebugActions::onKeyPressed(const Key &key)
{
    switch (key)
    {
    case Key::Num1:
        gameScene()->levelProperties()->increaseScore(100);
        break;
    case Key::Q:
        gameScene()->goGameOver();
        break;
    case Key::A:
        gameScene()->levelProperties()->nextLevel();
        break;
    }
}

void DebugActions::onKeyReleased(const Key &key)
{
}

const rptr<GameScene> DebugActions::gameScene()
{
    return attachedNodeAs<GameScene>();
}

} // namespace zoper

#endif
