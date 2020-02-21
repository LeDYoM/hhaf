#pragma once

#ifndef LIB_CORE_RENDER_TARGET_INCLUDE_HPP__
#define LIB_CORE_RENDER_TARGET_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/properties.hpp>

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
    RenderTarget(rptr<backend::IRenderTarget> renderTarget);

    /**
     * @brief Destroy the Render Target object
     */
    ~RenderTarget();

    void setViewPort(const Rectf32 &nviewport);
    Rectf32 viewPort() const;
    void setViewRect(const Rectf32 &nviewRect);
    Rectf32 viewRect() const;

    void draw(const scene::RenderData &renderData);
    void clear();

private:
    const rptr<backend::IRenderTarget> irender_target_;
};
} // namespace lib::sys

#endif
