HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>

#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::res
{
    class Shader;
}
namespace haf::scene
{
class HAF_API CameraComponent final
    : public component::ComponentBase<"CameraComponent">
{
public:
    enum class CameraMode : core::u32
    {
        Ortho = 0U,
        Frustum,
        Perspective
    };

    void onAttached() override;

    void setPerspective(core::f32 const fovy, core::f32 const aspect);
    prop::BasicProperty<core::vector4df> backgroundColor;
    prop::PropertyState<CameraMode> cameraMode;
    prop::PropertyState<core::f32> Left;
    prop::PropertyState<core::f32> Right;
    prop::PropertyState<core::f32> Bottom;
    prop::PropertyState<core::f32> Top;
    prop::PropertyState<core::f32> Near;
    prop::PropertyState<core::f32> Far;
    prop::PropertyState<core::vector3df> Position;
    prop::PropertyState<core::vector3df> Center;
    prop::PropertyState<core::vector3df> Up;

private:
    void cameraDataUpdated();
    void clearBackground();
    math::Matrix4x4 m_perspective_matrix;
    core::vector<res::Shader> m_shaders_with_camera_projection;
};
}  // namespace haf::scene

#endif
