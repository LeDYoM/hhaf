#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/renderizables_scene_node.hpp>

namespace haf::render
{
class Renderizable;
}

namespace haf::scene
{
class RenderizableSceneNode : public RenderizablesSceneNode
{
    using BaseClass = RenderizablesSceneNode;

public:
    using BaseClass::prop;

    RenderizableSceneNode(htps::rptr<SceneNode> parent, const htps::str& name);

    void buildNode(render::RenderizableBuilder const& node_builder);
    void buildNode(render::RenderizableBuilder&& node_builder);

    htps::sptr<render::Renderizable> node() noexcept;
    const htps::sptr<render::Renderizable> node() const noexcept;

private:
    htps::sptr<render::Renderizable> node_;
};
}  // namespace haf::scene

#endif
