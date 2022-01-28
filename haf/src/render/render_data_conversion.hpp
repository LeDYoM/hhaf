#ifndef HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP
#define HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP

#include <backend_dev/include/iprimitive_type.hpp>
#include <backend_dev/include/ivertex.hpp>
#include <backend_dev/include/iprimitive_type.hpp>
#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/ishader.hpp>
#include <haf/include/render/primitive_type.hpp>
#include <haf/include/render/vertex.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::render
{
backend::iPrimitiveType to_backend(
    const PrimitiveType primitive_type) noexcept;
backend::iVertex const* to_backend(Vertex const* vertices) noexcept;
backend::ITexture const* to_backend(res::ITexture const* texture);
backend::IShader const* to_backend(res::IShader const* shader);

}  // namespace haf::render

#endif
