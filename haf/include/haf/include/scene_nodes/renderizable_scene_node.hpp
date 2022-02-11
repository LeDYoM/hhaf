#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp> 
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene_nodes/renderizables_scene_node.hpp>

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
    using BaseClass::BaseClass;
    using BaseClass::prop;

    types::sptr<render::Renderizable> const& node() const noexcept;
};
}  // namespace haf::scene

#endif
