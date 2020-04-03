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
    void render(const IRenderData* render_data_begin,
                const IRenderData* render_data_end) override;

    void setViewPort(const mtps::Rectf32& nviewport) override;
    mtps::Rectf32 viewPort() const override;
    void setViewRect(const mtps::Rectf32& nviewRect) override;
    mtps::Rectf32 viewRect() const override;
    void clear() override;
};
}  // namespace lib::backend::sfmlb

#endif
