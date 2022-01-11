#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable_builder.hpp>

#include <haf/include/scene/scene_node.hpp>

using namespace haf::types;

namespace haf::scene
{
RenderizableSceneNode::RenderizableSceneNode(rptr<SceneNode> parent, str name) :
    BaseClass{std::move(parent), std::move(name)}, node_{}
{}

void RenderizableSceneNode::buildNode(
    render::RenderizableBuilder&& node_builder)
{
    node_ = createRenderizable(node_builder.extract());
}

sptr<render::Renderizable> const& RenderizableSceneNode::node() const noexcept
{
    return node_;
}

}  // namespace haf::scene
