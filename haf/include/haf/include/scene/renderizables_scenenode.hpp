#ifndef HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/scene/transformable_scenenode.hpp>
#include <haf/include/render/renderizables.hpp>

namespace haf::scene
{
class HAF_API RenderizablesSceneNode : public TransformableSceneNode,
                                       public render::Renderizables
{
    using BaseClass = TransformableSceneNode;

public:
    using BaseClass::prop;

    RenderizablesSceneNode(htps::rptr<SceneNode> parent, htps::str name);
};

}  // namespace haf::scene

#endif
