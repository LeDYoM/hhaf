#include "debug_actions.hpp"
#include "gamescene.hpp"
#include "levelproperties.hpp"

#include <haf/include/types/vector.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace zoper
{
using namespace haf::scene;
using namespace haf::input;

struct DebugActions::DebugActionsPrivate
{
    using DebugActionVectorType = haf::vector<
        haf::types::pair<haf::input::Key, DebugActions::DebugAction>>;
    using DebugActionVectorTypeIterator = DebugActionVectorType::iterator;
    DebugActionVectorType debug_actions_;

    DebugActionVectorTypeIterator find(Key const key)
    {
        debug_actions_.cfind_if(
            [key](DebugActionVectorType::value_type const element) {
                return element.first == key;
            });
    }

    
};

DebugActions::DebugActions() : p_{make_pimplp<DebugActionsPrivate>()}
{}

void DebugActions::addDebugAction(haf::input::Key const key,
                                  DebugAction debug_action)
{
    p_->debug_actions_.push_back({key, std::move(debug_action)});
}

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
