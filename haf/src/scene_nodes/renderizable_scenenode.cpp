#include <haf/include/scene_nodes/renderizable_scenenode.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable_builder.hpp>

#include <haf/include/scene/scenenode.hpp>

namespace haf::scene
{
RenderizableSceneNode::RenderizableSceneNode(htps::rptr<SceneNode> parent,
                                             const htps::str& name) :
    SceneNode{std::move(parent), name}, node_{}
{
    createRenderizables();
}

void RenderizableSceneNode::buildNode(RenderizableBuilder& node_builder)
{
    node_ = node_builder.create();
}

htps::sptr<Renderizable> RenderizableSceneNode::node() noexcept
{
    return node_;
}

const htps::sptr<Renderizable> RenderizableSceneNode::node() const noexcept
{
    return node_;
}
}  // namespace haf::scene
