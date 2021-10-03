#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/input/virtual_input_component.hpp>

namespace zoper
{
class GameScene;

class DebugActions : public haf::input::VirtualInputComponent
{
    using BaseClass = haf::input::VirtualInputComponent;
public:
    using DebugAction = haf::function<void()>;

    DebugActions();
    void addDebugAction(haf::input::Key const, DebugAction);
private:
    void onKeyPressed(haf::input::Key const& key) override;

    struct DebugActionsPrivate;
    haf::types::PImplPointer<DebugActionsPrivate> p_;
};
}  // namespace zoper

#endif
