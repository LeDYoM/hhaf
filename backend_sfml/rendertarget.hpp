#pragma once

#ifndef LIB_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>

namespace lib::scene
{
    struct Vertex;
}

namespace lib::backend::sfmlb
{
    class RenderTarget : public IRenderTarget, public sf::RenderTarget
    {
        void draw(const scene::Vertex *vertices, const u32 nVertex, const scene::PrimitiveType pType, const f32 *transform, const ITexture *texture) override;
        void setViewPort(const Rectf32 &nviewport) override;
        Rectf32 viewPort() const override;
        void setViewRect(const Rectf32 &nviewRect) override;
        Rectf32 viewRect() const override;
        void clear() override;
    };
}

#endif
