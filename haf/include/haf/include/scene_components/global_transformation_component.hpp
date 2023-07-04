HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <facil_math/include/matrix4x4.hpp>

#include <haf/include/events/receiver.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class HAF_API GlobalTransformationComponent final
    : public component::ComponentBootStrap<GlobalTransformationComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{
        "GlobalTransformationComponent"};

    GlobalTransformationComponent();
    ~GlobalTransformationComponent() override;

    void localTransformationChanged(fmath::Matrix4x4 const& localTransform);
    bool hasPendingMatrixUpdate() const noexcept;

private:
    evt::emitter<fmath::Matrix4x4 const&> m_globalTransformationChanged;
    void updateMatrix();
    void setModelViewMatrix();
    void globalTransformationChanged(fmath::Matrix4x4 const& parentMatrix);

    void onAttached() override;

    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};
}  // namespace haf::scene

#endif
