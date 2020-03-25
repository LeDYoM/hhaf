#include <lib/render/include/rendertarget.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <lib/render/include/renderdata.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/i_include/texture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/resources/i_include/shader.hpp>
#include <lib/scene/include/transform.hpp>
#include <lib/include/liblog.hpp>

namespace lib::sys
{
RenderTarget::RenderTarget(mtps::rptr<lib::backend::IRenderTarget> renderTarget)
    : irender_target_{std::move(renderTarget)}
{
    log_assert(renderTarget != nullptr, "renderTarget parameter is nullptr");
}

RenderTarget::~RenderTarget() = default;

void RenderTarget::draw(const scene::RenderData &renderData)
{
    irender_target_->draw(
        renderData.vArray.verticesArray().cbegin(),
        renderData.vArray.verticesArray().size(),
        renderData.vArray.primitiveType(),
        renderData.transform.getMatrix(),
        renderData.texture ? dynamic_cast<const scene::Texture *>(renderData.texture)->backEndTexture() : nullptr,
        renderData.shader ? dynamic_cast<const scene::Shader *>(renderData.shader)->backEndShader() : nullptr);
}

void RenderTarget::clear()
{
    irender_target_->clear();
}

mtps::Rectf32 RenderTarget::viewPort() const
{
    return irender_target_->viewPort();
}

void RenderTarget::setViewPort(const mtps::Rectf32 &nViewPort)
{
    irender_target_->setViewPort(nViewPort);
}

mtps::Rectf32 RenderTarget::viewRect() const
{
    return irender_target_->viewRect();
}

void RenderTarget::setViewRect(const mtps::Rectf32 &nViewRect)
{
    irender_target_->setViewRect(nViewRect);
}
} // namespace lib::sys
