HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_MOVE_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_MOVE_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/input/key.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class HAF_API MoveCameraComponent final
    : public component::ComponentBootStrap<MoveCameraComponent,"InputSubSystem">
{
public:
    static constexpr const core::str_view StaticTypeName{"MoveCameraComponent"};

    MoveCameraComponent();
    ~MoveCameraComponent() override;

    prop::PropertyState<core::f32> Speed;

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    void onAttached() override;
    bool addRequirements(component::ComponentRequirements&) override;

    void moveCamera(input::Key const& key);
};
}  // namespace haf::scene

#endif
