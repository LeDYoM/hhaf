#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/renderizables_scenenode.hpp>

namespace haf::scene
{
class Renderizable;

class RenderizableSceneNode : public RenderizablesSceneNode
{
    using BaseClass = RenderizablesSceneNode;

public:
    RenderizableSceneNode(htps::rptr<SceneNode> parent, const htps::str& name);
    void buildNode(render::RenderizableBuilder& node_builder);

    htps::sptr<Renderizable> node() noexcept;
    const htps::sptr<Renderizable> node() const noexcept;

private:
    htps::sptr<Renderizable> node_;
};
}  // namespace haf::scene

#endif
