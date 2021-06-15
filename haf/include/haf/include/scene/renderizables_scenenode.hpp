#ifndef HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLES_SCENENODE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/scene/scenenode.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace haf::scene
{
class Renderizables;

class HAF_API RenderizablesSceneNode : public SceneNode
{
    using BaseClass = SceneNode;

public:
    RenderizablesSceneNode(htps::rptr<SceneNode> parent, htps::str name);

    using SceneNodeProperties::prop;
    using TransformationProperties::prop;

    ~RenderizablesSceneNode();

    Renderizables& renderizables();
    Renderizables const& renderizables() const;

private:
    struct RenderizablesSceneNodePrivate;
    htps::PImplPointer<RenderizablesSceneNodePrivate> p_;
};

}  // namespace haf::scene

#endif
