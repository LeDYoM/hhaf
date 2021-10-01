#ifdef USE_DEBUG_ACTIONS

#include "debug_actions.hpp"
#include "gamescene.hpp"
#include "levelproperties.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace zoper
{
using namespace haf::scene;
using namespace haf::input;

void DebugActions::onKeyPressed(Key const& key)
{
    switch (key)
    {
        case Key::Num1:
            attachedNodeAs<GameScene>()->levelProperties()->increaseScore(100U);
            break;
        case Key::Q:
            attachedNodeAs<GameScene>()->goGameOver();
            break;
        case Key::A:
            attachedNodeAs<GameScene>()->levelProperties()->nextLevel();
            break;
        default:
            break;
    }
}

}  // namespace zoper

#endif
