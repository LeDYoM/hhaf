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
    : public component::ComponentBase<"DebugCameraComponent",
                                      input::KeyboardInputComponent,
                                      CameraComponent>
{
public:
    prop::PropertyState<core::f32> Speed;
    void onAttached() override;

private:
    void moveCamera(input::Key const& key);
    evt::ireceiver m_receiver;
};
}  // namespace haf::scene

#endif
