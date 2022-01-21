#include "render_data.hpp"
#include <backend_dev/include/irenderdata.hpp>
#include <haf/include/render/vertex.hpp>
#include <haf/include/render/primitive_type.hpp>
#include <haf/include/render/vertex_array.hpp>
#include "resources/texture.hpp"
#include "resources/shader.hpp"
#include <haf/include/scene/matrix4x4.hpp>

namespace
{
inline haf::backend::iVertex const* to_backend_member(
    haf::render::Vertex const* vertices) noexcept
{
    static_assert(
        sizeof(haf::backend::iVertex) == sizeof(haf::render::Vertex),
        "The scene Vertex and the backend Vertex do not have the same size");
    return reinterpret_cast<haf::backend::iVertex const*>(vertices);
}

inline haf::backend::iPrimitiveType to_backend_member(
    const haf::render::PrimitiveType primitive_type) noexcept
{
    static_assert(sizeof(haf::backend::iPrimitiveType) ==
                      sizeof(haf::render::PrimitiveType),
                  "The scene PrimitiveType and the backend PrimitiveType do "
                  "not have the same size");
    return static_cast<haf::backend::iPrimitiveType>(primitive_type);
}
}  // namespace

namespace haf::render
{

backend::IRenderData to_backend(RenderData const& render_data)
{
    return backend::IRenderData{
        to_backend_member(render_data.vArray.verticesArray().cbegin()),
        render_data.vArray.verticesArray().size(),
        to_backend_member(render_data.vArray.primitiveType()),
        render_data.transform.getMatrix(),
        render_data.texture
            ? dynamic_cast<haf::res::Texture const*>(render_data.texture)
                  ->backEndTexture()
            : nullptr,
        render_data.shader
            ? dynamic_cast<haf::res::Shader const*>(render_data.shader)
                  ->backEndShader()
            : nullptr};
}

}  // namespace haf::render
