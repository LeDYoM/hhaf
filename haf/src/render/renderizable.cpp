#include <haf/include/render/renderizable.hpp>
#include "render/renderizable_private.hpp"
#include "render_system.hpp"
#include "renderizable_internal_data.hpp"
#include "renderizable_internal_functions.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/resources/idefault_resources_retriever.hpp>

using namespace haf::core;
using namespace haf::scene;

namespace haf::render
{
Renderizable::Renderizable(rptr<SceneNode> parent,
                           RenderizableData&& renderizable_data) :
    sys::HasName{core::move(renderizable_data.RenderizableName())},
    m_parent{core::move(parent)},
    m_p{make_pimplp<RenderizablePrivate>(
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
        m_material.shader =
            m_parent->subSystem<res::IDefaultResourcesRetriever>()
                ->getDefaultShader();
    }
}

Renderizable::~Renderizable() = default;

rptr<SceneNode> Renderizable::parent() noexcept
{
    return m_parent;
}

rptr<SceneNode const> Renderizable::parent() const noexcept
{
    return m_parent;
}

void Renderizable::render(bool const parent_transformation_changed)
{
    if (visible())
    {
        update(parent_transformation_changed);
        m_p->render();
    }
}

void Renderizable::update(bool const parent_transformation_changed)
{
    if (parent_transformation_changed)
    {
        auto parent_transformation_component{
            parent()->component<Transformation>()};
        m_p->m_render_element.setModelViewMatrix(
            parent_transformation_component->globalTransform().getMatrix());
    }

    if (m_material.shader.readResetHasChanged())
    {
        //        p_->m_render_element.setShader(to_backend(m_material.shader().get()));
    }

    if (m_material.textureRect.readResetHasChanged())
    {
        m_p->updateTextureRect(m_material.textureRect());
    }

    if (m_material.color.readResetHasChanged())
    {
        m_p->updateColors(m_material.color());
    }

    if (m_material.texture.readResetHasChanged())
    {
        m_p->m_render_element.setTexture(
            to_backend(m_material.texture().get()));
    }
}

}  // namespace haf::render
