HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLE_INTERNAL_FUNCTIONS_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_INTERNAL_FUNCTIONS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <haf/include/render/renderizable.hpp>
#include <backend_dev/include/ivertex.hpp>

namespace haf::render
{
void setColor(htps::vector<backend::iColor>& colors, scene::Color const& color);
void setQuad(htps::vector<backend::iPosition>& positions);
void setPolygon(htps::vector<backend::iPosition>& positions);
void setTextureRect(
    htps::vector<backend::iPosition> const& positions,
    htps::vector<backend::iTextureCoordinates>& texture_coordinates,
    htps::Rectf32 const& texture_rect);

}  // namespace haf::render

#endif
