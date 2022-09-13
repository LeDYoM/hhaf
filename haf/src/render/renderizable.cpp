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
        renderizable_data.PointCount(),
        renderizable_data.FigureTypeProperty(),
        sys::getSystem<sys::RenderSystem>(parent).currentRenderTarget())}
{
    m_material.texture     = renderizable_data.TextureProperty();
    m_material.textureRect = renderizable_data.TextureRectProperty();
    m_material.shader      = renderizable_data.ShaderProperty();
    m_material.color       = renderizable_data.ColorProperty();

    if (m_material.shader() == nullptr)
    {
        m_material.shader = parent_->subSystem<res::IDefaultResourcesRetriever>()
                             ->getDefaultShader();
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

    if (m_material.shader.readResetHasChanged())
    {
//        p_->m_render_element.setShader(to_backend(m_material.shader().get()));
    }

    if (m_material.textureRect.readResetHasChanged())
    {
        p_->updateTextureRect(m_material.textureRect());
    }

    if (m_material.color.readResetHasChanged())
    {
        p_->updateColors(m_material.color());
    }

    if (m_material.texture.readResetHasChanged())
    {
        p_->m_render_element.setTexture(to_backend(m_material.texture().get()));
    }
}

}  // namespace haf::render
