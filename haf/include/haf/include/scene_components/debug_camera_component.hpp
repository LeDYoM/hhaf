HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_DEBUG_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_DEBUG_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/events/receiver.hpp>
#include <haf/include/input/key.hpp>

#include <haf/include/component/component_declaration.hpp>

namespace haf::input
{
class KeyboardInputComponent;
}
namespace haf::scene
{
class CameraComponent;
class HAF_API DebugCameraComponent final
    : public component::ComponentBootStrap<DebugCameraComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{
        "DebugCameraComponent"};

    DebugCameraComponent();
    ~DebugCameraComponent() override;

    prop::PropertyState<core::f32> Speed;
    void onAttached() override;

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    bool addRequirements(component::ComponentRequirements&) override;

    void logCameraData();
    void moveCamera(input::Key const& key);
};
}  // namespace haf::scene

#endif
