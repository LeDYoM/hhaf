#include "rendertarget.hpp"

#include <lib/include/backend/irendertarget.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/scene/texture.hpp>

namespace lib::core
{
    RenderTarget::RenderTarget(lib::backend::IRenderTarget*renderTarget)
        : m_renderTarget{renderTarget}
    {

    }

    RenderTarget::~RenderTarget()
    {

    }

    void RenderTarget::draw(const scene::RenderData & renderData)
    {
        m_renderTarget->draw(
            &(renderData.vArray.verticesArray()[0]),
            renderData.vArray.verticesArray().size(),
            renderData.vArray.primitiveType(),
            renderData.transform.getMatrix(),
                renderData.texture ? renderData.texture->backEndTexture() : nullptr);
    }

    void RenderTarget::clear()
    {
        m_renderTarget->clear();
    }

    const lib::Rectf32&lib::core::RenderTarget::viewPort()
    {

    }

    void lib::core::RenderTarget::setViewPort(lib::Rectf32 nViewPort)
    {

    }

    const lib::Rectf32&lib::core::RenderTarget::viewRect()
    {

    }

    void lib::core::RenderTarget::setViewRect(lib::Rectf32 nViewRect)
    {

    }
}
