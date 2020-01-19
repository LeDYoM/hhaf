#include <lib/render/include/rendertarget.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/texture.hpp>
#include <lib/resources/include/shader.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/scene/transform.hpp>
#include <lib/include/liblog.hpp>

namespace lib::sys
{
RenderTarget::RenderTarget(rptr<lib::backend::IRenderTarget> renderTarget)
    : m_renderTarget{std::move(renderTarget)}
{
    log_assert(renderTarget != nullptr, "renderTarget parameter is nullptr");
}

RenderTarget::~RenderTarget() = default;

void RenderTarget::draw(const scene::RenderData &renderData)
{
    m_renderTarget->draw(
        renderData.vArray.verticesArray().cbegin(),
        renderData.vArray.verticesArray().size(),
        renderData.vArray.primitiveType(),
        renderData.transform.getMatrix(),
        renderData.texture ? dynamic_cast<const scene::Texture *>(renderData.texture)->backEndTexture() : nullptr,
        renderData.shader ? dynamic_cast<const scene::Shader *>(renderData.shader)->backEndShader() : nullptr);
}

void RenderTarget::clear()
{
    m_renderTarget->clear();
}

Rectf32 RenderTarget::viewPort() const
{
    return m_renderTarget->viewPort();
}

void RenderTarget::setViewPort(const Rectf32 &nViewPort)
{
    m_renderTarget->setViewPort(nViewPort);
}

Rectf32 RenderTarget::viewRect() const
{
    return m_renderTarget->viewRect();
}

void RenderTarget::setViewRect(const Rectf32 &nViewRect)
{
    m_renderTarget->setViewRect(nViewRect);
}
} // namespace lib::sys
