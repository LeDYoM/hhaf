HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP
#define HAF_RENDER_RENDER_DATA_CONVERSION_INCLUDE_HPP

#include <backend_dev/include/ivertex.hpp>
#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/ishader.hpp>
#include <haf/include/render/vertex.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::render
{
backend::iColor to_backend(scene::Color const& color) noexcept;
backend::ITexture const* to_backend(res::ITexture const* texture);
backend::IShader const* to_backend(res::IShader const* shader);

}  // namespace haf::render

#endif
