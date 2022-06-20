HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>

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

    htps::sptr<render::Renderizable> const& node() const noexcept;
};
}  // namespace haf::scene

#endif
