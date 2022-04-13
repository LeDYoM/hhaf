#include "render_data_conversion.hpp"
#include <haf/include/render/vertex.hpp>
#include "resources/texture.hpp"
#include "resources/shader.hpp"
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::render
{
backend::iVertex const* to_backend(Vertex const* vertices) noexcept
{
    static_assert(
        sizeof(haf::backend::iVertex) == sizeof(haf::render::Vertex),
        "The scene Vertex and the backend Vertex do not have the same size");
    return reinterpret_cast<haf::backend::iVertex const*>(vertices);
}

backend::iColor to_backend(scene::Color const& color) noexcept
{
    static_assert(sizeof(scene::Color) == sizeof(backend::iColor),
                  "Error in conversion to backend color");
    return backend::iColor{color.red(), color.green(), color.blue(),
                           color.alpha()};
}

backend::ITexture const* to_backend(res::ITexture const* texture)
{
    return texture
        ? dynamic_cast<res::Texture const*>(texture)->backEndTexture()
        : nullptr;
}

backend::IShader const* to_backend(res::IShader const* shader)
{
    return shader ? dynamic_cast<res::Shader const*>(shader)->backEndShader()
                  : nullptr;
}

}  // namespace haf::render
