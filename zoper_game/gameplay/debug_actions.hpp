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

    void onKeyPressed(haf::input::Key const& key) override;
};
}  // namespace zoper

#endif

#endif