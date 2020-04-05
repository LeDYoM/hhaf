#include <lib/render/include/rendertarget.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irenderdata.hpp>
#include <lib/render/include/renderdata.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/i_include/texture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/resources/i_include/shader.hpp>
#include <lib/scene/include/transform.hpp>
#include <lib/include/liblog.hpp>

using namespace mtps;

namespace haf::sys
{
RenderTarget::RenderTarget(rptr<haf::backend::IRenderTarget> renderTarget) :
    irender_target_{std::move(renderTarget)}
{
    log_assert(renderTarget != nullptr, "renderTarget parameter is nullptr");
}

RenderTarget::~RenderTarget() = default;

inline void do_render(const rptr<backend::IRenderTarget> irender_target_,
                      const scene::RenderData& renderData)
{
    backend::IRenderData render_data{
        renderData.vArray.verticesArray().cbegin(),
        renderData.vArray.verticesArray().size(),
        renderData.vArray.primitiveType(),
        renderData.transform.getMatrix(),
        renderData.texture
            ? dynamic_cast<const scene::Texture*>(renderData.texture)
                  ->backEndTexture()
            : nullptr,
        renderData.shader
            ? dynamic_cast<const scene::Shader*>(renderData.shader)
                  ->backEndShader()
            : nullptr};

    irender_target_->render(&render_data, &render_data + 1);
}

void RenderTarget::render(rptr<const scene::RenderData> render_data_begin,
                          rptr<const scene::RenderData> render_data_end)
{
    while (render_data_begin != render_data_end)
    {
        do_render(irender_target_, *(render_data_begin++));
    }
}

void RenderTarget::clear()
{
    irender_target_->clear();
}

Rectf32 RenderTarget::viewPort() const
{
    return irender_target_->viewPort();
}

void RenderTarget::setViewPort(const Rectf32& nViewPort)
{
    irender_target_->setViewPort(nViewPort);
}

Rectf32 RenderTarget::viewRect() const
{
    return irender_target_->viewRect();
}

void RenderTarget::setViewRect(const Rectf32& nViewRect)
{
    irender_target_->setViewRect(nViewRect);
}
}  // namespace haf::sys
