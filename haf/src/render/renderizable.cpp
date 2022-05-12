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
    sys::HasName{htps::move(renderizable_data.prop<RenderizableName>()())},
    parent_{htps::move(parent)},
    p_{make_pimplp<RenderizablePrivate>(
        this,
        renderizable_data.prop<PointCount>()(),
        renderizable_data.prop<FigureTypeProperty>()(),
        sys::getSystem<sys::RenderSystem>(parent).currentRenderTarget())}
{
    put<TextureProperty>(renderizable_data.prop<TextureProperty>()())
        .put<TextureRectProperty>(
            renderizable_data.prop<TextureRectProperty>()())
        .put<ShaderProperty>(renderizable_data.prop<ShaderProperty>()())
        .put<ColorProperty>(renderizable_data.prop<ColorProperty>()());

    if (prop<ShaderProperty>()() == nullptr)
    {
//        prop<ShaderProperty>() =
//            parent_->subSystem<res::IDefaultResourcesRetriever>()
//                ->getDefaultShader();
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
        p_->render_element_->setModelViewMatrix(
            parent()->globalTransform().getMatrix());
    }

    if (ps_readResetHasAnyChanged(prop<TextureRectProperty>()))
    {
        p_->updateTextureRect();
    }

    if (ps_readResetHasAnyChanged(prop<ColorProperty>()))
    {
        p_->updateColors();
    }

    if (prop<TextureProperty>().readResetHasChanged())
    {
        p_->render_element_->setTexture(
            to_backend(prop<TextureProperty>()().get()));
    }

    if (prop<ShaderProperty>().readResetHasChanged())
    {
/*        if (prop<ShaderProperty>()() != nullptr)
        {
            types::sptr<res::IShader> const& shader{
                prop<ShaderProperty>()()};

            if (prop<TextureProperty>()() != nullptr)
            {
                shader->setUniform("has_texture", true);
                shader->setUniform("texture", prop<TextureProperty>()().get());
            }
            else
            {
                shader->setUniform("has_texture", false);
            }
        }
*/
        p_->render_element_->setShader(
            to_backend(prop<ShaderProperty>()().get()));
    }
}

}  // namespace haf::render
