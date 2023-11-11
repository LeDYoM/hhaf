HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/math/types.hpp>

#include <haf/include/events/receiver.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class HAF_API GlobalTransformationComponent final
    : public component::ComponentBootStrap<GlobalTransformationComponent,
                                           "GlobalViewUpdaterSubSystem">
{
public:
    static constexpr const core::str_view StaticTypeName{
        "GlobalTransformationComponent"};

    GlobalTransformationComponent();
    ~GlobalTransformationComponent() override;

    void localTransformationChanged(math::Matrix4x4 const& localTransform);
    bool hasPendingMatrixUpdate() const noexcept;

private:
    evt::emitter<math::Matrix4x4 const&> m_globalTransformationChanged;
    void updateMatrix();
    void setModelViewMatrix();
    void globalTransformationChanged(math::Matrix4x4 const& parentMatrix);
    void connectToParentGlobalTransformationChanged();
    void onAttached() override;
    bool addRequirements(
        component::ComponentRequirements& component_requirements) override;

    struct ComponentsRequired;
    haf::core::PImplPointer<ComponentsRequired> m_components;

    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};
}  // namespace haf::scene

#endif
