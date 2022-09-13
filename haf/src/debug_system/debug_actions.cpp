#include <haf/include/debug_system/debug_actions.hpp>
#include <htypes/include/vector.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <hlog/include/hlog.hpp>

using namespace haf::input;
using namespace htps;

namespace haf::debug
{
struct DebugActions::DebugActionsPrivate final
{
    using DebugActionVectorType = vector<
        pair<input::Key, DebugActions::DebugAction>>;
    using DebugActionVectorTypeIterator = DebugActionVectorType::iterator;
    DebugActionVectorType debug_actions_;

    DebugActionsPrivate() = default;
    ~DebugActionsPrivate() = default;

    auto find(Key const key)
    {
        auto const iterator{debug_actions_.cfind_if(
            [key](DebugActionVectorType::value_type const element) {
                return element.first == key;
            })};
        return std::make_pair(iterator != debug_actions_.cend(), iterator);
    }
};

DebugActions::DebugActions() : p_{make_pimplp<DebugActionsPrivate>()}
{}

DebugActions::~DebugActions() = default;

void DebugActions::addDebugAction(haf::input::Key const key,
                                  DebugAction debug_action)
{
    p_->debug_actions_.push_back({key, htps::move(debug_action)});
}

void DebugActions::onKeyPressed(Key const& key)
{
    auto element{p_->find(key)};
    if (element.first)
    {
        element.second->second();
    }
}

void DebugActions::logSceneNodeTree()
{
    DisplayLog::debug("---------------------------------------------------");
    logSceneNodeTree(attachedNode(), 0U);
    DisplayLog::debug("---------------------------------------------------");
}

void DebugActions::logSceneNodeTree(rptr<scene::SceneNode const> scene_node,
                                    size_type level)
{
    str complete(level * 4U);
    for (size_type i{0U}; i<level; ++i)
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

}  // namespace haf::debug
