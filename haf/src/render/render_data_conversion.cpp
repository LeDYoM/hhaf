#include "render_data_conversion.hpp"
#include <haf/include/render/vertex.hpp>
#include <haf/include/render/primitive_type.hpp>
#include <haf/include/render/vertex_array.hpp>
#include "resources/texture.hpp"
#include "resources/shader.hpp"
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::render
{

backend::iPrimitiveType to_backend(const PrimitiveType primitive_type) noexcept
{
    static_assert(sizeof(backend::iPrimitiveType) == sizeof(PrimitiveType),
                  "The scene PrimitiveType and the backend PrimitiveType do "
                  "not have the same size");
    return static_cast<backend::iPrimitiveType>(primitive_type);
}

backend::iVertex const* to_backend(Vertex const* vertices) noexcept
{
    static_assert(
        sizeof(haf::backend::iVertex) == sizeof(haf::render::Vertex),
        "The scene Vertex and the backend Vertex do not have the same size");
    return reinterpret_cast<haf::backend::iVertex const*>(vertices);
}

backend::ITexture const* to_backend(res::ITexture const* texture)
{
    return texture
        ? dynamic_cast<res::Texture const*>(texture)->backEndTexture()
        : nullptr;
}

backend::IShader const* to_backend(res::IShader const* shader)
{
    return shader
        ? dynamic_cast<res::Shader const*>(shader)->backEndShader()
        : nullptr;
}

}  // namespace haf::render
