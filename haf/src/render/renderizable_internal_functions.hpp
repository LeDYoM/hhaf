#pragma once

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
htps::vector2dd getPositionFromAngleAndRadius(const scene::FigType_t fig_type,
                                              const htps::f64 angle,
                                              const htps::vector2df& radius);

htps::pair<scene::PrimitiveType, htps::size_type>
initDataVertexPerFigureAndNumPoints(const scene::FigType_t fig_type,
                                    const htps::size_type num_points) noexcept;

htps::Rects32 textureFillQuad(
    const htps::sptr<res::ITexture>& texture) noexcept;

htps::vector2df normalizeInBox(
    const htps::vector2df& position,
    scene::Renderizable::RenderizableInternalData const& data);

void updateColorForVertex(
    scene::Renderizable::RenderizableInternalData const& data,
    scene::BasicVertexArray::value_type& vertex);

void updateColors(scene::BasicVertexArray& vertices,
                  scene::Renderizable::RenderizableInternalData const& data);

void updateTextureCoordsAndColorForVertex(
    const scene::BasicVertexArray::iterator v_iterator,
    scene::Renderizable::RenderizableInternalData const& iData);

void updateTextureCoordsAndColor(
    scene::BasicVertexArray& vertices,
    scene::Renderizable::RenderizableInternalData const& data);

void updateGeometry(scene::BasicVertexArray& vertices,
                    scene::Renderizable::RenderizableInternalData const& data);
}  // namespace haf::render

#endif
