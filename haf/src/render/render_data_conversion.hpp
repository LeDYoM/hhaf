#ifndef HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP
#define HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP

#include <backend_dev/include/irenderdata.hpp>
#include "render_data.hpp"

namespace haf::render
{
backend::iPrimitiveType to_backend(
    const PrimitiveType primitive_type) noexcept;
backend::iVertex const* to_backend(Vertex const* vertices) noexcept;
backend::ITexture const* to_backend(res::ITexture const* texture);
backend::IShader const* to_backend(res::IShader const* shader);

backend::IRenderData to_backend(RenderData const& render_data);

}  // namespace haf::render

#endif
