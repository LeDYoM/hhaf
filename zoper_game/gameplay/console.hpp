#ifndef HAF_CONSOLE_INCLUDE_HPP
#define HAF_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/scene/include/scenenode.hpp>

namespace zoper
{
class Console : public haf::scene::SceneNode
{
public:
    using haf::scene::SceneNode::SceneNode;

    void onCreated() override;
};
}  // namespace zoper

#endif