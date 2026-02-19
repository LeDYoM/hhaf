export module haf:debug:debug_actions;

import :virtual_input_component;
import :core;
import scene:scene_node;

namespace haf::debug
{
struct DebugActions::DebugActionsPrivate final
{
    using DebugActionVectorType =
        vector<pair<input::Key, DebugActions::DebugAction>>;
    using DebugActionVectorTypeIterator = DebugActionVectorType::iterator;
    DebugActionVectorType debug_actions_;

    DebugActionsPrivate()  = default;
    ~DebugActionsPrivate() = default;

    auto find(Key const key)
    {
        auto const iterator{debug_actions_.cfind_if(
            [key](DebugActionVectorType::value_type const element) {
                return element.first == key;
            })};
        return pair(iterator != debug_actions_.cend(), iterator);
    }
};

class DebugActions : public input::VirtualInputComponent
{
    using BaseClass = input::VirtualInputComponent;

public:
    using DebugAction = htps::function<void()>;

    DebugActions() : p_{make_pimplp<DebugActionsPrivate>()} {}

    ~DebugActions() override = default;

    void addDebugAction(input::Key const, DebugAction)
    {
        p_->debug_actions_.push_back({key, htps::move(debug_action)});
    }

    void logSceneNodeTree()
    {
        DisplayLog::debug(
            "---------------------------------------------------");
        logSceneNodeTree(attachedNode(), 0U);
        DisplayLog::debug(
            "---------------------------------------------------");
    }

    void logSceneNodeTree(htps::rptr<scene::SceneNode const> scene_node,
                          htps::size_type level)
    {
        str complete(level * 4U);
        for (size_type i{0U}; i < level; ++i)
        {
            complete += "    ";
        }
        complete += scene_node->name();
        DisplayLog::debug(complete);

        for (auto&& node : scene_node->sceneNodes())
        {
            logSceneNodeTree(node.get(), level + 1U);
        }
    }

private:
    void onKeyPressed(input::Key const& key) override
    {
        auto element{p_->find(key)};
        if (element.first)
        {
            element.second->second();
        }
    }

    struct DebugActionsPrivate;
    htps::PImplPointer<DebugActionsPrivate> p_;
};
}  // namespace haf::debug
