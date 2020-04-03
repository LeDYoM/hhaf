#pragma once

#ifndef LIB_CORE_RENDER_TARGET_INCLUDE_HPP
#define LIB_CORE_RENDER_TARGET_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

namespace lib::backend
{
class IRenderTarget;
}
namespace lib::scene
{
class RenderData;
}

namespace lib::sys
{
/**
 * @brief Class to encapsulate a Render target from the render target interface.
 *
 * This class is to be used to export the functionality of the render target
 * interface into a concrete class.
 */
class RenderTarget
{
public:
    /**
     * @brief Construct a new RenderTarget object
     *
     * @param renderTarget Interface to the underlying low level render target.
     */
    RenderTarget(mtps::rptr<backend::IRenderTarget> renderTarget);

    /**
     * @brief Destroy the Render Target object
     */
    ~RenderTarget();

    void setViewPort(const mtps::Rectf32& nviewport);
    mtps::Rectf32 viewPort() const;
    void setViewRect(const mtps::Rectf32& nviewRect);
    mtps::Rectf32 viewRect() const;

    void draw(const scene::RenderData& renderData);
    void drawBatch(mtps::rptr<const scene::RenderData> render_data_begin,
                   mtps::rptr<const scene::RenderData> render_data_end);
    void clear();

private:
    const mtps::rptr<backend::IRenderTarget> irender_target_;
};
}  // namespace lib::sys

#endif
