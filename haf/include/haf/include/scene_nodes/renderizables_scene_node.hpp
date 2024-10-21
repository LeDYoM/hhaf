HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/render/renderizables.hpp>

namespace haf::scene
{
class HAF_API RenderizablesSceneNode : public TransformableSceneNode
{
    using SceneNodeBaseClass = TransformableSceneNode;

public:
    RenderizablesSceneNode(htps::rptr<SceneNode> parent, htps::str name);
    void postRender(SceneRenderContext& sceneRenderContext) override;

    auto renderizablesCount() const noexcept { return renderizables_.size(); }

    bool emptyRenderizables() const noexcept { return renderizables_.empty(); }

    decltype(auto) operator[](htps::size_type const index) const noexcept
    {
        return renderizables_[index];
    }

    auto renderizableBuilder()
    {
        return renderizables_.renderizableBuilder();
    }

private:
    render::Renderizables renderizables_;
};

}  // namespace haf::scene

#endif
