HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/scene_components/debug_camera_component.hpp>

namespace haf::scene
{
class HAF_API SceneComponent final
    : public component::ComponentBootStrap<SceneComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{"SceneComponent"};

    SceneComponent();
    ~SceneComponent() override;

private:
    bool addRequirements(component::ComponentRequirements&) override;

    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
};

}  // namespace haf::scene

#endif
