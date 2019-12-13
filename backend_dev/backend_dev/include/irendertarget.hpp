#pragma once

#ifndef LIB_BACKEND_RENDER_TARGET_INCLUDE_HPP
#define LIB_BACKEND_RENDER_TARGET_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <lib/scene/vertexarray.hpp>
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
            const u32 nVertex,
            const scene::PrimitiveType pType,
            const f32 *transform,
            const ITexture *texture,
            const IShader *shader) = 0;

        virtual void setViewPort(const Rectf32 &nviewport) = 0;
        virtual Rectf32 viewPort() const = 0;
        virtual void setViewRect(const Rectf32 &nviewRect) = 0;
        virtual Rectf32 viewRect() const = 0;

        virtual void clear() = 0;
    };
}

#endif
