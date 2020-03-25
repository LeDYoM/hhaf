#pragma once

#ifndef LIB_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define LIB_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/include/vertex.hpp>
#include <lib/scene/include/vertexarray.hpp>
#include "itexture.hpp"
#include "ishader.hpp"

namespace lib::backend
{
class IRenderTarget
{
public:
    virtual ~IRenderTarget() {}

    virtual void draw(
        const scene::Vertex *vertices,
        const mtps::u32 nVertex,
        const scene::PrimitiveType pType,
        const mtps::f32 *transform,
        const ITexture *texture,
        const IShader *shader) = 0;

    virtual void setViewPort(const mtps::Rectf32 &nviewport) = 0;
    virtual mtps::Rectf32 viewPort() const = 0;
    virtual void setViewRect(const mtps::Rectf32 &nviewRect) = 0;
    virtual mtps::Rectf32 viewRect() const = 0;

    virtual void clear() = 0;
};
} // namespace lib::backend

#endif
