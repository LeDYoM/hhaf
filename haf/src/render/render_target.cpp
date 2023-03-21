#include "render_target.hpp"

#include <htypes/include/span.hpp>
#include <hlog/include/hlog.hpp>
#include <hogl/include/render_target.hpp>

using namespace htps;

namespace haf::sys
{
RenderTarget::RenderTarget() :
    irender_target_{msptr<ogl::RenderTarget>()}, render_element_container_{}
{}

void RenderTarget::draw(ogl::RenderElement const& render_element)
{
    render_element_container_.push_back(&render_element);
}

void RenderTarget::update()
{
//    irender_target_->clear();

    if (Projection.readResetHasChanged())
    {
//        irender_target_->setProjection(span<f32 const>(
//            Projection().getMatrix(), Projection().getMatrix() + 16));
    }

    if (ViewPort.readResetHasChanged())
    {
//        irender_target_->setViewPort(ViewPort());
    }

//    for (auto&& render_element : render_element_container_)
    {
//        render_element->updateInternalData();
/*        auto* const shader{render_element->shader};

        if (shader)
        {
            shader->setTexture(0U, render_element->texture);
            shader->bind();
        }

        irender_target_->render(render_element);

        if (shader)
        {
            shader->unbind();
        }
*/
    }
}

void RenderTarget::clearRenderQueue()
{
    render_element_container_.clear();
}

}  // namespace haf::sys
