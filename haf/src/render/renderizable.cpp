#include <haf/include/render/renderizable.hpp>
#include "render/renderizable_private.hpp"
#include "render_system.hpp"
#include "renderizable_internal_data.hpp"
#include "renderizable_internal_functions.hpp"
#include "system/get_system.hpp"

#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/resources/idefault_resources_retriever.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{
Renderizable::Renderizable(rptr<TransformableSceneNode> parent,
                           RenderizableData&& renderizable_data) :
    sys::HasName{htps::move(renderizable_data.RenderizableName())},
    parent_{htps::move(parent)},
    p_{make_pimplp<RenderizablePrivate>(
        this,
        renderizable_data.PointCount(),
        renderizable_data.FigureTypeProperty(),
        sys::getSystem<sys::RenderSystem>(parent).currentRenderTarget())}
{
    TextureProperty     = renderizable_data.TextureProperty();
    TextureRectProperty = renderizable_data.TextureRectProperty();
    ShaderProperty      = renderizable_data.ShaderProperty();
    ColorProperty       = renderizable_data.ColorProperty();

    if (ShaderProperty() == nullptr)
    {
        //        ShaderProperty =
        //        parent_->subSystem<res::IDefaultResourcesRetriever>()
        //                             ->getDefaultShader();
    }
}

Renderizable::~Renderizable() = default;

rptr<TransformableSceneNode> Renderizable::parent() noexcept
{
    return parent_;
}

rptr<TransformableSceneNode const> Renderizable::parent() const noexcept
{
    return parent_;
}

void Renderizable::render(bool const parent_transformation_changed)
{
    if (visible())
    {
        update(parent_transformation_changed);
        p_->render();
    }
}

void Renderizable::update(bool const parent_transformation_changed)
{
    if (parent_transformation_changed)
    {
        p_->m_render_element.setModelViewMatrix(
            parent()->globalTransform().getMatrix());
    }

    if (ps_readResetHasAnyChanged(TextureRectProperty))
    {
        p_->updateTextureRect();
    }

    if (ps_readResetHasAnyChanged(ColorProperty))
    {
        p_->updateColors();
    }

    if (TextureProperty.readResetHasChanged())
    {
        p_->m_render_element.setTexture(to_backend(TextureProperty().get()));
    }

    if (ShaderProperty.readResetHasChanged())
    {
/*        if (ShaderProperty() != nullptr)
        {
            sptr<res::IShader> const& shader{ShaderProperty()};

            if (TextureProperty() != nullptr)
            {
                shader->setUniform("has_texture", true);
                shader->setUniform("texture", TextureProperty().get());
            }
            else
            {
                shader->setUniform("has_texture", false);
            }
        }
        p_->m_render_element.setShader(to_backend(ShaderProperty().get()));
        */
    }
}

}  // namespace haf::render
