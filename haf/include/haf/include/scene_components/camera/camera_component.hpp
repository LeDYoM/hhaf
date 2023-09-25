HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/events/emitter.hpp>

#include <facil_math/include/matrix4x4.hpp>
#include <haf/include/component/component_declaration.hpp>

#include <haf/include/resources/shader.hpp>

namespace haf::scene
{
class HAF_API CameraComponent final
    : public component::ComponentBootStrap<CameraComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{"CameraComponent"};

    CameraComponent();
    ~CameraComponent();

    enum class CameraMode : core::u32
    {
        None = 0U,
        Ortho = 1U,
        Frustum = 2U,
        Perspective = 3U
    };

    void onAttached() override;

    prop::PropertyState<CameraMode> cameraMode;
    prop::PropertyState<core::f32> Left;
    prop::PropertyState<core::f32> Right;
    prop::PropertyState<core::f32> Bottom;
    prop::PropertyState<core::f32> Top;
    prop::PropertyState<core::f32> Near;
    prop::PropertyState<core::f32> Far;
    prop::PropertyState<fmath::vector3df> Position;
    prop::PropertyState<fmath::vector3df> Center;
    prop::PropertyState<fmath::vector3df> Up;
    prop::PropertyState<core::f32> FovY;
    prop::PropertyState<core::f32> Aspect;

    evt::emitter<> cameraPerspectiveUpdated;
    evt::emitter<> cameraViewUpdated;
    evt::emitter<> cameraUpdated;

private:
    void cameraDataPerspectiveUpdated();
    void cameraDataViewUpdated();
    void performCameraUpdate();

    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};
}  // namespace haf::scene

#endif