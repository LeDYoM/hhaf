HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_MESH_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_RENDER_MESH_RENDER_CONTEXT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/resources/shader.hpp>
#include <haf/include/properties/property_state.hpp>

namespace haf::render
{
class MeshRenderContext
{
public:
    prop::PropertyState<math::Matrix4x4> modelViewMatrix;
    core::sptr<res::Shader> shader;
};

}  // namespace haf::render

#endif
