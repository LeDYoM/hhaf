#ifndef HAF_SCENE_NODES_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_NODES_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/types/scene_types.hpp>

namespace haf::scene
{
class HAF_API CameraComponent : public component::ComponentForType<Scene>
{
    using BaseClass = component::ComponentForType<Scene>;

public:

    htps::PropertyState<SceneBox> view;
    htps::PropertyState<SceneQuad> viewPort;

    void onAttached() override;
    void update() override;

private:
    struct CameraSceneNodePrivate;
    htps::PImplPointer<CameraSceneNodePrivate> p_;
};
}  // namespace haf::scene

#endif
