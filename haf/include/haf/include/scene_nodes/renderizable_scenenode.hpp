#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/scenenode.hpp>

namespace haf::scene
{
class Renderizable;

class RenderizableSceneNode : public SceneNode
{
public:
    using BaseClass = SceneNode;

    RenderizableSceneNode(htps::rptr<SceneNode> parent, const htps::str& name);
    void buildNode(RenderizableBuilder& node_builder);

    htps::sptr<Renderizable> node() noexcept;
    const htps::sptr<Renderizable> node() const noexcept;

private:
    htps::sptr<Renderizable> node_;
};
}  // namespace haf::scene

#endif
