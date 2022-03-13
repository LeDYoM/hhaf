#ifndef ZOPER_DEBUG_ACTIONS_INCLUDE_HPP
#define ZOPER_DEBUG_ACTIONS_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/input/virtual_input_component.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::debug
{
class DebugActions : public input::VirtualInputComponent
{
    using BaseClass = input::VirtualInputComponent;

public:
    using DebugAction = function<void()>;

    DebugActions();
    ~DebugActions() override;
    void addDebugAction(input::Key const, DebugAction);
    void logSceneNodeTree();
    void logSceneNodeTree(htps::rptr<scene::SceneNode const> scene_node,
                          htps::size_type level);

private:
    void onKeyPressed(input::Key const& key) override;

    struct DebugActionsPrivate;
    types::PImplPointer<DebugActionsPrivate> p_;
};
}  // namespace haf::debug

#endif
