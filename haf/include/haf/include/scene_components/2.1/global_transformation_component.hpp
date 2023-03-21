HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_GLOBAL_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/properties/property_state.hpp>

#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/events/receiver.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/render/has_mesh_render_context.hpp>

namespace haf::render
{
class MeshRenderContext;
}

namespace haf::scene
{
class HAF_API GlobalTransformationComponent final
    : public component::ComponentBase<"GlobalTransformationComponent">,
      public render::HasMeshRenderContext
{
public:
    void onAttached() override;

    void localTransformationChanged(math::Matrix4x4 const& localTransform);

    bool hasPendingMatrixUpdate() const noexcept;

private:
    void updateMatrix();
    void globalTransformationChanged(math::Matrix4x4 const& parentMatrix);

    evt::ireceiver m_receiver;
    math::Matrix4x4 m_transform;
    prop::PropertyState<math::Matrix4x4> m_localTransformation;
    prop::PropertyState<math::Matrix4x4> m_parentGlobalTransformation;
    evt::emitter<math::Matrix4x4 const&> m_globalTransformationChanged;
};
}  // namespace haf::scene

#endif
