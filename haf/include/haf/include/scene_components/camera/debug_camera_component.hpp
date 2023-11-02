HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_DEBUG_CAMERA_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_DEBUG_CAMERA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>

#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class HAF_API DebugCameraComponent final
    : public component::ComponentBootStrap<DebugCameraComponent,
                                           "InternalControllerSubSystem">
{
public:
    static constexpr const core::str_view StaticTypeName{
        "DebugCameraComponent"};

    DebugCameraComponent();
    ~DebugCameraComponent() override;

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    void onAttached() override;
    bool addRequirements(component::ComponentRequirements&) override;

    void logCameraData();
};
}  // namespace haf::scene

#endif
