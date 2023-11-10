HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_PROPERTIES_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/math/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class HAF_API SceneRenderPropertiesComponent final
    : public component::ComponentBootStrap<SceneRenderPropertiesComponent, "">
{
public:
    static constexpr const core::str_view StaticTypeName{
        "SceneRenderPropertiesComponent"};

    SceneRenderPropertiesComponent();
    ~SceneRenderPropertiesComponent() override;

    void onAttached() override;

    void setViewMatrix(math::Matrix4x4 const& matrix);

private:
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};
}  // namespace haf::scene

#endif
