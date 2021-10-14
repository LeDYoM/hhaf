#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable_builder.hpp>

#include <haf/include/scene/scene_node.hpp>

namespace haf::scene
{
RenderizableSceneNode::RenderizableSceneNode(htps::rptr<SceneNode> parent,
                                             const htps::str& name) :
    BaseClass{std::move(parent), name}, node_{}
{}

void RenderizableSceneNode::buildNode(
    render::RenderizableBuilder& node_builder)
{
    node_ = node_builder.create();
}

htps::sptr<render::Renderizable> RenderizableSceneNode::node() noexcept
{
    return node_;
}

const htps::sptr<render::Renderizable> RenderizableSceneNode::node()
    const noexcept
{
    return node_;
}
}  // namespace haf::scene
