HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODES_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_NODES_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <htypes/include/properties/iproperty.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/types/scene_types.hpp>

namespace haf::scene
{
class HAF_API CameraComponent : public component::ComponentForType<Scene>
{
    using BaseClass = component::ComponentForType<Scene>;

public:
    CameraComponent();
    ~CameraComponent() override;

    htps::PropertyState<SceneBox> view;
    htps::PropertyState<SceneQuad> viewPort;

    void moveView(SceneCoordinates const& delta);

    void onAttached() override;
    void update() override;

private:
    struct CameraComponentPrivate;
    htps::PImplPointer<CameraComponentPrivate> p_;
};
}  // namespace haf::scene

#endif
