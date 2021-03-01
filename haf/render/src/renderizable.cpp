#include <haf/render/include/renderizable.hpp>

#include <render/i_include/rendersystem.hpp>
#include <render/i_include/renderizable_internal_data.hpp>
#include <render/i_include/renderizable_internal_functions.hpp>
#include <system/i_include/get_system.hpp>

#include <haf/render/include/renderdata.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/render/include/renderizable_builder.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <haf/render/include/vertexarray.hpp>
#include <haf/render/include/renderdata.hpp>

using namespace htps;

namespace haf::scene
{

struct Renderizable::RenderizablePrivate
{
    VertexArray vertices_;
    RenderData render_data_;
    rptr<Renderizable const> const i_this_;

    RenderizablePrivate(FigType_t const figure_type,
                        size_type const initial_point_count,
                        Matrix4x4 const& matrix,
                        rptr<res::ITexture> texture,
                        rptr<res::IShader> shader,
                        rptr<Renderizable const> i_this) :
        vertices_{initDataVertexPerFigureAndNumPoints(figure_type,
                                                      initial_point_count)},
        render_data_{vertices_, matrix, texture, shader},
        i_this_{std::move(i_this)}
    {}

    Renderizable::RenderizableInternalData getMomentumInternalData() const
    {
        return {i_this_->figType(), i_this_->box(),
                i_this_->color(),   i_this_->pointCount(),
                i_this_->shader(),  i_this_->textureRect(),
                i_this_->texture(), i_this_->color_modifier()};
    }
};

Renderizable::Renderizable(rptr<SceneNode> _parent,
                           str name,
                           FigType_t const figure_type,
                           size_type const initial_point_count,
                           Rectf32 _box,
                           Color _color,
                           sptr<res::ITexture> _texture,
                           sptr<res::IShader> _shader) :
    sys::HasName{std::move(name)},
    SceneNodeParent{_parent},
    p_{make_pimplp<RenderizablePrivate>(figure_type,
                                        initial_point_count,
                                        parent()->globalTransform(),
                                        texture().get(),
                                        shader().get(), this)},
    figType{figure_type},
    pointCount{initial_point_count},
    box{std::move(_box)},
    color{std::move(_color)},
    shader{std::move(_shader)},
    textureRect{textureFillQuad(_texture)},
    texture{std::move(_texture)}
{}

Renderizable::~Renderizable() = default;

void Renderizable::render()
{
    if (visible())
    {
        update();

        if (!p_->vertices_.empty())
        {
            sys::getSystem<sys::RenderSystem>(parent()).draw(p_->render_data_);
        }
    }
}

void Renderizable::setTextureAndTextureRect(sptr<res::ITexture> texture_,
                                            const Rectf32& textRect)
{
    textureRect = static_cast<Rects32>(textRect);
    texture.set(std::move(texture_));
}

void Renderizable::setTextureFill(sptr<res::ITexture> texture_)
{
    setTextureAndTextureRect(texture_, textureFillQuad(texture_));
}

void Renderizable::update()
{
    auto const& mi_data{p_->getMomentumInternalData()};

    if (ps_readResetHasAnyChanged(box, figType, pointCount))
    {
        updateGeometry(p_->vertices_.verticesArray(), mi_data);
        textureRect.resetHasChanged();
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(textureRect))
    {
        updateTextureCoordsAndColor(p_->vertices_.verticesArray(), mi_data);
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(color, color_modifier))
    {
        updateColors(p_->vertices_.verticesArray(), mi_data);
    }

    if (ps_readResetHasChanged(texture))
    {
        p_->render_data_.texture = texture().get();
    }

    if (ps_readResetHasChanged(shader))
    {
        p_->render_data_.shader = shader().get();
    }
}

}  // namespace haf::scene
