#ifndef HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/vertex_array.hpp>
#include "render_data.hpp"
#include "renderizable_internal_functions.hpp"
#include <backend_dev/include/irenderdata.hpp>
#include "render_data_conversion.hpp"

using namespace htps;
using namespace haf::scene;

namespace haf::render
{

struct Renderizable::RenderizablePrivate
{
    rptr<TransformableSceneNode> parent_;
    VertexArray vertices_;
    RenderData render_data_;
    backend::IRenderData irender_data_;
    rptr<Renderizable const> const i_this_;

    RenderizablePrivate(rptr<TransformableSceneNode> parent,
                        FigType_t const figure_type,
                        size_type const initial_point_count,
                        Matrix4x4 const& matrix,
                        rptr<res::ITexture> texture,
                        rptr<res::IShader> shader,
                        rptr<Renderizable const> i_this) :
        parent_{parent},
        vertices_{initDataVertexPerFigureAndNumPoints(figure_type,
                                                      initial_point_count)},
        render_data_{vertices_, matrix, texture, shader, &irender_data_},
        irender_data_{to_backend(render_data_)},
        i_this_{std::move(i_this)}
    {}

    constexpr RenderizableInternalData getMomentumInternalData() const noexcept
    {
        return {i_this_->prop<FigureTypeProperty>()(),
                i_this_->prop<BoxProperty>()(),
                i_this_->prop<ColorProperty>()(),
                i_this_->prop<PointCount>()(),
                i_this_->prop<ShaderProperty>()(),
                i_this_->prop<TextureRectProperty>()(),
                i_this_->prop<TextureProperty>()(),
                i_this_->prop<ColorModifierProperty>()()};
    }

    void updateBackendData()
    {
        irender_data_ = to_backend(render_data_);
    }
};

}  // namespace haf::render

#endif
