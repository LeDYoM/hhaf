#ifndef HAF_RENDER_RENDERIZABLE_INTERNAL_FUNCTIONS_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_INTERNAL_FUNCTIONS_INCLUDE_HPP

#include <htypes/include/vector2d.hpp>

#include <haf/include/render/renderizable.hpp>
#include <haf/include/render/primitivetype.hpp>
#include <haf/include/render/vertexarray.hpp>
#include "renderizable_internal_data.hpp"

namespace haf::render
{
/**
 * @brief Get the Position From angle and radius
 * Get the expected vector position for a given fig_type angle and radius.
 * This function will perform different calculations depending on the
 * @b fig_type parameter.
 *
 * @param fig_type Enum value with the figure we use
 * @param angle Current angle to use
 * @param radius The radius of the figure
 * @return vector2dd Position vector
 */
htps::vector2dd getPositionFromAngleAndRadius(FigType_t const fig_type,
                                              htps::f64 const angle,
                                              htps::vector2df const& radius);

/**
 * @brief Get the init data for a vertex array
 *
 * @param fig_type Figure type to create
 * @param num_points Initial number of points
 * @return pair<PrimitiveType, size_type> Initialization data for a vertex
 * array
 */
htps::pair<PrimitiveType const, htps::size_type const>
initDataVertexPerFigureAndNumPoints(FigType_t const fig_type,
                                    htps::size_type const num_points) noexcept;
/**
 * @brief Get the rectange for a given texture
 *
 * @param texture Texture where to extract the Rect
 * @return Rects32 Quad around the texture if it is not nullptr
 */
htps::Rects32 textureFillQuad(
    htps::sptr<res::ITexture const> const& texture) noexcept;

htps::vector2df normalizeInBox(
    htps::vector2df const& position,
    RenderizableInternalData const& data) noexcept;

void updateColorForVertex(RenderizableInternalData const& data,
                          BasicVertexArray::value_type& vertex);

void updateColors(BasicVertexArray& vertices,
                  RenderizableInternalData const& data);

void updateTextureCoordsAndColorForVertex(
    BasicVertexArray::iterator const v_iterator,
    RenderizableInternalData const& iData);

void updateTextureCoordsAndColor(
    BasicVertexArray& vertices,
    RenderizableInternalData const& data);

void updateGeometry(BasicVertexArray& vertices,
                    RenderizableInternalData const& data);
}  // namespace haf::render

#endif
