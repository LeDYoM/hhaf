HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/render/renderizables.hpp>

namespace haf::scene
{
class HAF_API RenderizablesSceneNode : public TransformableSceneNode,
                                       public render::Renderizables
{
    using SceneNodeBaseClass = TransformableSceneNode;

public:

    RenderizablesSceneNode(htps::rptr<SceneNode> parent, htps::str name);
    void postRender(SceneRenderContext& sceneRenderContext) override;
};

}  // namespace haf::scene

#endif
