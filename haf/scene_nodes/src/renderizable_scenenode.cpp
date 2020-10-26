#include <haf/scene_nodes/include/renderizable_scenenode.hpp>
#include <mtypes/include/types.hpp>
#include <haf/render/include/renderizable.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/render/include/renderizable_builder.hpp>

#include <haf/scene/include/scenenode.hpp>

namespace haf::scene
{
RenderizableSceneNode::RenderizableSceneNode(mtps::rptr<SceneNode> parent,
                                             const mtps::str& name) :
    SceneNode{std::move(parent), name}, node_{}
{}

void RenderizableSceneNode::buildNode(RenderizableBuilder& node_builder)
{
    node_ = node_builder.create();
}

mtps::sptr<Renderizable> RenderizableSceneNode::node() noexcept
{
    return node_;
}
const mtps::sptr<Renderizable> RenderizableSceneNode::node() const noexcept
{
    return node_;
}
}  // namespace haf::scene
