#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp> 
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

    RenderizableSceneNode(types::rptr<SceneNode> parent, types::str name);

    void buildNode(render::RenderizableBuilder&& node_builder);

    types::sptr<render::Renderizable> const& node() const noexcept;

private:
    types::sptr<render::Renderizable> node_;
};
}  // namespace haf::scene

#endif
