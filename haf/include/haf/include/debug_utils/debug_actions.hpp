#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/input/virtual_input_component.hpp>

namespace haf::debug
{
class DebugActions : public input::VirtualInputComponent
{
    using BaseClass = input::VirtualInputComponent;

public:
    using DebugAction = function<void()>;

    DebugActions();
    void addDebugAction(input::Key const, DebugAction);

private:
    void onKeyPressed(input::Key const& key) override;

    struct DebugActionsPrivate;
    types::PImplPointer<DebugActionsPrivate> p_;
};
}  // namespace haf::debug

#endif
