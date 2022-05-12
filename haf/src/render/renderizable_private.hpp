HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include "renderizable_internal_functions.hpp"
#include <backend_dev/include/irender_element.hpp>
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
    backend::IRenderElement* render_element_{nullptr};

    RenderizablePrivate(rptr<Renderizable const> i_this,
                        size_type const num_vertex,
                        FigType_t const figure_type,
                        sptr<sys::RenderTarget> render_target) :
        i_this_{i_this},
        num_vertex_{num_vertex},
        figure_type_{figure_type},
        render_target_{htps::move(render_target)},
        render_element_{render_target_->createRenderElement()}
    {
        positions_.resize(num_vertex_);
        colors_.resize(num_vertex_);
        texture_coordinates_.resize(num_vertex_);
        render_element_->setSize(num_vertex_);
        updatePositions();
    }

    ~RenderizablePrivate()
    {
        render_target_->destroyRenderElement(render_element_);
    }

    void render()
    {
        if (render_element_ != nullptr)
        {
            render_target_->draw(render_element_);
        }
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
        render_element_->setPositions(positions_.cbegin());
    }

    void updateTextureRect()
    {
        setTextureRect(positions_, texture_coordinates_,
                       i_this_->prop<TextureRectProperty>()());
        render_element_->setTexturecoordinates(texture_coordinates_.cbegin());
    }

    void updateColors()
    {
        setColor(colors_, i_this_->prop<ColorProperty>()());
        render_element_->setColors(colors_.cbegin());
    }
};

}  // namespace haf::render

#endif
