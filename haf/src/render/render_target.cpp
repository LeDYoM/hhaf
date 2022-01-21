#include "render_target.hpp"

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irenderdata.hpp>
#include "render_data.hpp"
#include <haf/include/resources/itexture.hpp>
#include "resources/texture.hpp"
#include <haf/include/resources/ishader.hpp>
#include "resources/shader.hpp"
#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/render/vertex_array.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace
{
inline haf::backend::iVertex const* to_backend(
    haf::render::Vertex const* vertices) noexcept
{
    static_assert(
        sizeof(haf::backend::iVertex) == sizeof(haf::render::Vertex),
        "The scene Vertex and the backend Vertex do not have the same size");
    return reinterpret_cast<haf::backend::iVertex const*>(vertices);
}

inline haf::backend::iPrimitiveType to_backend(
    const haf::render::PrimitiveType primitive_type) noexcept
{
    static_assert(sizeof(haf::backend::iPrimitiveType) ==
                      sizeof(haf::render::PrimitiveType),
                  "The scene PrimitiveType and the backend PrimitiveType do "
                  "not have the same size");
    return static_cast<haf::backend::iPrimitiveType>(primitive_type);
}

inline void do_render(rptr<haf::backend::IRenderTarget> const irender_target_,
               const haf::render::RenderData& renderData)
{
    auto rd = renderData.irender_data;
    irender_target_->render(rd, rd + 1);
}

}  // namespace
namespace haf::sys
{
RenderTarget::RenderTarget(rptr<haf::backend::IRenderTarget> renderTarget) :
    irender_target_{std::move(renderTarget)}
{
    LogAsserter::log_assert(renderTarget != nullptr,
                            "renderTarget parameter is nullptr");
}

RenderTarget::~RenderTarget() = default;

void RenderTarget::render(
    rptr<render::RenderData const> const render_data_begin,
    rptr<render::RenderData const> const render_data_end)
{
    auto render_data_begin_temp{render_data_begin};

    while (render_data_begin_temp != render_data_end)
    {
        do_render(irender_target_, *(render_data_begin_temp++));
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
