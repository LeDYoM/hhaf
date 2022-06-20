HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include "renderizable_internal_functions.hpp"
#include "render_element.hpp"
#include "render_data_conversion.hpp"
#include "render_target.hpp"
#include "resources/texture.hpp"
#include "resources/shader.hpp"
#include "renderizable_internal_data.hpp"
#include <backend_dev/include/ivertex.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{

struct Renderizable::RenderizablePrivate
{
    rptr<Renderizable const> const i_this_;
    size_type num_vertex_;
    FigType_t figure_type_;
    vector<backend::iPosition> positions_;
    vector<backend::iColor> colors_;
    vector<backend::iTextureCoordinates> texture_coordinates_;
    sptr<sys::RenderTarget> render_target_;
    RenderElement m_render_element;

    RenderizablePrivate(rptr<Renderizable const> i_this,
                        size_type const num_vertex,
                        FigType_t const figure_type,
                        sptr<sys::RenderTarget> render_target) :
        i_this_{i_this},
        num_vertex_{num_vertex},
        figure_type_{figure_type},
        render_target_{htps::move(render_target)},
        m_render_element{render_target_->createRenderElement()}
    {
        positions_.resize(num_vertex_);
        colors_.resize(num_vertex_);
        texture_coordinates_.resize(num_vertex_);
        m_render_element.setSize(num_vertex_);
        updatePositions();
    }

    void render()
    {
        render_target_->draw(m_render_element);
    }

    void updatePositions()
    {
        switch (figure_type_)
        {
            case FigType_t::Sprite:
            {
                setQuad(positions_);
            }
            break;

            case FigType_t::PolygonSprite:
            {
                setPolygon(positions_);
            }
            break;
        }
        m_render_element.setPositions(positions_.cbegin());
    }

    void updateTextureRect()
    {
        setTextureRect(positions_, texture_coordinates_,
                       i_this_->TextureRectProperty());
        m_render_element.setTexturecoordinates(texture_coordinates_.cbegin());
    }

    void updateColors()
    {
        setColor(colors_, i_this_->ColorProperty());
        m_render_element.setColors(colors_.cbegin());
    }
};

}  // namespace haf::render

#endif
