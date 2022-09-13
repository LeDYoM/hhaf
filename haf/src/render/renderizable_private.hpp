HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include "renderizable_internal_functions.hpp"
#include <hogl/include/render_element.hpp>
#include "render_data_conversion.hpp"
#include "render_target.hpp"
#include "resources/texture.hpp"
#include "resources/shader.hpp"
#include "renderizable_internal_data.hpp"
#include <backend_dev/include/ivertex.hpp>

namespace haf::render
{
struct Renderizable::RenderizablePrivate
{
    FigType_t figure_type_;
    htps::vector<backend::iPosition> positions_;
    htps::vector<backend::iColor> colors_;
    htps::vector<backend::iTextureCoordinates> texture_coordinates_;
    htps::sptr<sys::RenderTarget> render_target_;
    ogl::RenderElement m_render_element;

    RenderizablePrivate(htps::size_type const num_vertex,
                        FigType_t const figure_type,
                        htps::sptr<sys::RenderTarget> render_target);

    void render();

    void updatePositions();

    void updateTextureRect(htps::Rects32 const& textureRect);

    void updateColors(scene::Color const& color);
};

}  // namespace haf::render

#endif
