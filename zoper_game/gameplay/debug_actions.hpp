#ifdef USE_DEBUG_ACTIONS

#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/input/virtual_input_component.hpp>

namespace zoper
{
class GameScene;

class DebugActions : public haf::input::VirtualInputComponent
{
private:
    using BaseClass = haf::component::IComponent;

    void onKeyPressed(const haf::input::Key& key) override;
    void onKeyReleased(const haf::input::Key& key) override;

    htps::rptr<GameScene> gameScene();
};
}  // namespace zoper

#endif

#endif